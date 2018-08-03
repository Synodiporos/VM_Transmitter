/*
 * BatteryMonitor.cpp
 *
 *  Created on: Jul 3, 2018
 *      Author: sgeorgiadis
 */

#include "BatteryMonitor.h"
#include "Arduino.h"

BatteryMonitor::BatteryMonitor(uint8_t pinNumber,
		uint8_t spv,
		unsigned short int measPeriod,
		unsigned short int alarmTriggerValue,
		unsigned short int hysteresis,
		unsigned short int dischargeValue,
		unsigned short int fullchargeValue) :
		analogPin(pinNumber),
		spv(spv),
		measPeriod(measPeriod),
		dischargeValue(dischargeValue),
		fullchargeValue(fullchargeValue),
		alarmTriggerValue(alarmTriggerValue),
		hysteresis(hysteresis){
	initialize();
}

BatteryMonitor::~BatteryMonitor() {
	// TODO Auto-generated destructor stub
}

void BatteryMonitor::initialize(){
	clearRecordsTable();
}

void BatteryMonitor::startRecord(){
	state = 2;
}

void BatteryMonitor::pauseRecord(){
	state = 1;
}

void BatteryMonitor::stopRecord(){
	clearRecordsTable();
	state = 0;
}

void BatteryMonitor::clearRecordsTable(){
	for (unsigned int i = 0; i < spv; i++)
		readings[i] = 0;
	total = 0;
	readIndex = 0;
	flag = 0;
}

void BatteryMonitor::setDischargeValue(short int dischargeValue){
	this->dischargeValue = dischargeValue;
}

short int BatteryMonitor::getDischargeValue(){
	return this->dischargeValue;
}

void BatteryMonitor::setFullchargeValue(short int fullchargeValue){
	this->fullchargeValue = fullchargeValue;
}

short int BatteryMonitor::getFullchargeValue(){
	return this->fullchargeValue;
}

void BatteryMonitor::setMeasurementPeriod(short int measPeriod){
	this->measPeriod = measPeriod;
}

short int BatteryMonitor::getMeasurementPeriod(){
	return this->measPeriod;
}

void BatteryMonitor::setAlarmTriggerValue(unsigned short int atv){
	this->alarmTriggerValue = atv;
}

unsigned short int BatteryMonitor::getAlarmTriggerValue(){
	return this->alarmTriggerValue;
}

void BatteryMonitor::setHysteresis(short int hysteresis){
	this->hysteresis = hysteresis;
}

short int BatteryMonitor::getHysteresis(){
	return this->hysteresis;
}

bool BatteryMonitor::isAlarmEnabled(){
	return this->alarm;
}

unsigned short int BatteryMonitor::getMeasurementValue(){
	return this->measurement;
}

uint8_t BatteryMonitor::getPercentage(){

	return MathUtil::mapRange(getMeasurementValue(),
			getDischargeValue(),
			getFullchargeValue(),
			(short int)0, (short int)100);
}

float BatteryMonitor::getVoltage(float aref){
	return MathUtil::map(getMeasurementValue(),
				0, 1023, 0, aref);
}

void BatteryMonitor::addBatteryMonitorListener(
		IBatteryMonitorListener* listener){
	this->batteryListeners.push_back(listener);
}

void BatteryMonitor::removeBatteryMonitorListener(
		IBatteryMonitorListener* listener){
	for (std::vector<IBatteryMonitorListener*>::iterator it =
			batteryListeners.begin();
			it != batteryListeners.end(); ++it){
		if( *it == listener)
			batteryListeners.erase(it);
	}
}

IBatteryMonitorListener* BatteryMonitor::
	getBatteryMonitorListener(
			unsigned short int index){
	return *(batteryListeners.begin() + index);
}

std::vector<IBatteryMonitorListener*> BatteryMonitor::
	getBatteryMonitorListeners(){
	return this->batteryListeners;
}

void BatteryMonitor::onValueChanged(unsigned short int oldValue){
	notifyBatteryValueChanged(oldValue);
	if(this->alarm){
		if(this->getMeasurementValue() >
				(this->getAlarmTriggerValue()
						+ this->getHysteresis())){
			this->alarm = false;
			onAlarmStateChanged();
			notifyBatteryTriggerAlarmStateChanged();
		}
	}
	else{
		if(this->getMeasurementValue() <= (this->getAlarmTriggerValue())){
			this->alarm = true;
			onAlarmStateChanged();
			notifyBatteryTriggerAlarmStateChanged();
		}
	}
	Serial.println((int)alarm);
}

void BatteryMonitor::validate(){
	if(state==2 && millis()-time >= measPeriod){
		// subtract the last reading:
		total = total - readings[readIndex];
		// read from the sensor:
		readings[readIndex] = analogRead(analogPin);
		// add the reading to the total:
		total = total + readings[readIndex];
		// advance to the next position in the array:
		readIndex = readIndex + 1;
		int count = readIndex;
		if(flag==1)
			count = spv;
		// calculate the average:
		unsigned short int average = (total / count) + BATTM_OFFSET;
		// if we're at the end of the array...
		if (readIndex >= spv) {
			// ...wrap around to the beginning:
			readIndex = 0;
			flag = 1;
			time = millis();

			//Check if average value has changed
			if(average != measurement){
				//Update the analogeValue value
				unsigned short int old = measurement;
				measurement = average;
				onValueChanged(old);
			}
		}
	}
}

void BatteryMonitor::onAlarmStateChanged(){

}

void BatteryMonitor::notifyBatteryValueChanged(short int oldValue){
	for (std::vector<IBatteryMonitorListener*>::iterator it =
			batteryListeners.begin() ;
			it != batteryListeners.end(); ++it){
		(*it)->onBatteryValueChanged(this,
				oldValue);
	}
}

void BatteryMonitor::notifyBatteryTriggerAlarmStateChanged(){
	for (std::vector<IBatteryMonitorListener*>::iterator it =
			batteryListeners.begin() ;
			it != batteryListeners.end(); ++it){
		(*it)->onBatteryTriggerAlarmStateChanged(
				this, this->alarm);
	}
}
