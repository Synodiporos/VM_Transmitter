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
		measPeriod(measPeriod),
		dischargeValue(dischargeValue),
		fullchargeValue(fullchargeValue),
		alarmTriggerValue(alarmTriggerValue),
		hysteresis(hysteresis),
		analog(ToggleAnalogInput(pinNumber, spv))
{
	initialize();
}

BatteryMonitor::~BatteryMonitor() {
	// TODO Auto-generated destructor stub
}

void BatteryMonitor::initialize(){
	int br = getMeasurementPeriod()/analog.getSPV();
	int mil = 1023/br;
	timer = Timer(mil, br, 0);
	timer.setActionListener(this);
}

void BatteryMonitor::startRecord(){
	timer.start();
}

void BatteryMonitor::pauseRecord(){
	timer.pause();
}

void BatteryMonitor::stopRecord(){
	timer.stop();
	this->analog.clearRecordsTable();
}

AnalogInput* BatteryMonitor::getAnalogInput(){
	return &this->analog;
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


unsigned short int BatteryMonitor::getValue(){
	return this->analog.getAnalogValue();
}

uint8_t BatteryMonitor::getPercentage(){
	return MathUtil::mapRange(analog.getAnalogValue(),
			getDischargeValue(),
			getFullchargeValue(),
			(short int)0, (short int)100);
}

float BatteryMonitor::getVoltage(float aref){
	return MathUtil::map(analog.getAnalogValue(),
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

void BatteryMonitor::actionPerformed(Action action){
	unsigned short int act =
			*(unsigned short int*)action.getContainer();
	if(act==Timer::TIMER_TIC){
		analog.validate();
	}
	else if(act==Timer::TIMER_STOP){
		unsigned short int value = analog.getAnalogValue();
		if(value!=oldMeas){
			onValueChanged(oldMeas);
			notifyBatteryValueChanged(oldMeas);
			oldMeas = value;
		}
		timer.start();
	}
}

void BatteryMonitor::onValueChanged(unsigned short int oldValue){
	if(!this->alarm){
		if(this->getValue() >
				(this->getAlarmTriggerValue()
						+ this->getHysteresis())){
			this->alarm = true;
			onAlarmStateChanged();
			notifyBatteryTriggerAlarmStateChanged();
		}
	}
	else{
		if(this->getValue() <= (this->getAlarmTriggerValue())){
			this->alarm = false;
			onAlarmStateChanged();
			notifyBatteryTriggerAlarmStateChanged();
		}
	}
}

void BatteryMonitor::validate(){
	timer.validate();
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
