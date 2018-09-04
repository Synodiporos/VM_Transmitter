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
	unsigned int meas = toIntValue(analogRead(BT_ANALOG_PIN));
	filter = FilterOnePole(LOWPASS, BATTM_FREQ, meas);
	setMeasurement(filter.input(meas));
}

void BatteryMonitor::measure(){
	state = 0;
	time = millis();
	unsigned int meas = toIntValue(analogRead(BT_ANALOG_PIN));
	filter = FilterOnePole(LOWPASS, BATTM_FREQ, meas);
}
/*
void BatteryMonitor::startRecord(){
	state = 2;
}

void BatteryMonitor::pauseRecord(){
	state = 1;
}

void BatteryMonitor::stopRecord(){
	state = 0;
}*/

bool BatteryMonitor::isAlarmEnabled(){
	return this->alarm;
}

float BatteryMonitor::getMeasurementValue(){
	return (float)this->measurement/100;
}

uint8_t BatteryMonitor::getPercentage(){
	float meas = getMeasurementValue();
	if(meas<=BATTM_DISC_VALUE)
		return 0;
	else if(meas>=BATTM_FULL_VALUE)
		return 100;
	else
		return ((meas - BATTM_DISC_VALUE)/
				(BATTM_FULL_VALUE-BATTM_DISC_VALUE))*100;
}

float BatteryMonitor::getVoltage(float aref){
	return ((float)getMeasurementValue() * aref) / 1023;
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
	unsigned int meas = getMeasurementValue();
	if(this->alarm){
		if(meas >
				(BATTM_ALARM_VALUE + BATTM_HYSTERISIS_VALUE)){
			this->alarm = false;
			onAlarmStateChanged();
			notifyBatteryTriggerAlarmStateChanged();
		}
	}
	else{
		if(meas <= BATTM_ALARM_VALUE){
			this->alarm = true;
			onAlarmStateChanged();
			notifyBatteryTriggerAlarmStateChanged();
		}
	}
}

void BatteryMonitor::validate(){
	/*if(state==2 && millis()-time >= BATTM_MEAS_PERIOD){
		int value = toIntValue(analogRead(BT_ANALOG_PIN));
		unsigned int meas = filter.input( value );
		//unsigned int meas = analogRead(BT_ANALOG_PIN);
		setMeasurement(meas);
		time = millis();
		//Serial.println(analogRead(BT_ANALOG_PIN)/1);
	}*/

	unsigned long interval = millis() - time;
	if(interval>=BATTM_INTERVAL && state<BATTM_ITERS){
		int value = toIntValue(analogRead(BT_ANALOG_PIN));
		unsigned int meas = filter.input( value );
		//unsigned int meas = analogRead(BT_ANALOG_PIN);
		if(state==BATTM_ITERS-1)
			setMeasurement(meas);
		time = millis();
		state++;
	}
}

void BatteryMonitor::setMeasurement(unsigned int meas){
	if(this->measurement!=meas){
		this->measurement = meas;
		onValueChanged(meas);
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

int BatteryMonitor::toIntValue(unsigned int value){
	float vout =
			(value * AREF_VOLTAGE / 1023);

	/*Serial.print("BAT value: ");
	Serial.print(value);
	Serial.print(" vout: ");
	Serial.println(vout);*/

	float vin = (vout/BATTM_FACTOR) + BATTM_OFFSET;
	return vin * 100;
}
