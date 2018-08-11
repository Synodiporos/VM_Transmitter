/*
 * BatteryMonitor.cpp
 *
 *  Created on: Jul 3, 2018
 *      Author: sgeorgiadis
 */

#include "BatteryMonitor.h"
#include "Arduino.h"

BatteryMonitor* BatteryMonitor::instance = nullptr;

BatteryMonitor::BatteryMonitor(){
	initialize();
}

BatteryMonitor::~BatteryMonitor() {
	// TODO Auto-generated destructor stub
}

BatteryMonitor* BatteryMonitor::getInstance(){
	if(!instance)
		instance = new BatteryMonitor();
	return instance;
}

void BatteryMonitor::initialize(){

}

void BatteryMonitor::startRecord(){
	state = 2;
}

void BatteryMonitor::pauseRecord(){
	state = 1;
}

void BatteryMonitor::stopRecord(){
	state = 0;
}

bool BatteryMonitor::isAlarmEnabled(){
	return this->alarm;
}

unsigned short int BatteryMonitor::getMeasurementValue(){
	return this->measurement;
}

uint8_t BatteryMonitor::getPercentage(){
	return MathUtil::mapRange(getMeasurementValue(),
			BATTM_DISC_VALUE,
			BATTM_FULL_VALUE,
			(short int)0, (short int)100);
}

float BatteryMonitor::getVoltage(float aref){
	return MathUtil::map(getMeasurementValue(),
				0, 1023, 0, aref);
}

void BatteryMonitor::setBatteryMonitorListener(
		IBatteryMonitorListener* listener){
	this->listener = listener;
}

IBatteryMonitorListener* BatteryMonitor::getBatteryMonitorListener(){
	return this->listener;
}

void BatteryMonitor::onValueChanged(unsigned short int oldValue){
	notifyBatteryValueChanged(oldValue);
	if(this->alarm){
		if(this->getMeasurementValue() >
				(BATTM_ALARM_VALUE + BATTM_HYSTERISIS_VALUE)){
			this->alarm = false;
			onAlarmStateChanged();
			notifyBatteryTriggerAlarmStateChanged();
		}
	}
	else{
		if(this->getMeasurementValue() <= BATTM_ALARM_VALUE){
			this->alarm = true;
			onAlarmStateChanged();
			notifyBatteryTriggerAlarmStateChanged();
		}
	}
}

void BatteryMonitor::validate(){
	if(state==2 && millis()-time >= BATTM_MEAS_PERIOD){
		unsigned int meas =
				((int)filter.input( analogRead(BT_ANALOG_PIN)/4 )) *4;
		if(this->measurement!=meas){
			this->measurement = meas;
			onValueChanged(meas);
		}
		time = millis();
		//Serial.println(analogRead(BT_ANALOG_PIN)/1);
	}
}

void BatteryMonitor::onAlarmStateChanged(){

}

void BatteryMonitor::notifyBatteryValueChanged(short int oldValue){
	IBatteryMonitorListener* l = getBatteryMonitorListener();
	if(l)
		l->onBatteryValueChanged(this, oldValue);
}

void BatteryMonitor::notifyBatteryTriggerAlarmStateChanged(){
	IBatteryMonitorListener* l = getBatteryMonitorListener();
	if(l)
		l->onBatteryTriggerAlarmStateChanged(
				this, this->alarm);
}
