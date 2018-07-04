/*
 * Controller.cpp
 *
 *  Created on: Jul 4, 2018
 *      Author: sgeorgiadis
 */

#include "Controller.h"

Controller::Controller(){

}

Controller::~Controller() {
	// TODO Auto-generated destructor stub
}

void Controller::activate(){
	if(batteryMonitor)
		batteryMonitor->startRecord();
	if(hvProbe)
		hvProbe->startRecord();
	if(notification){
		notification->notifyActive();
		notification->notifyWarning();
	}
}

void Controller::deactivate(){
	if(batteryMonitor)
		batteryMonitor->stopRecord();
	if(hvProbe)
		hvProbe->stopRecord();
	if(notification)
		notification->stopNotify();
}

void Controller::setBatteryMonitor(BatteryMonitor* batteryMonitor){
	if(this->batteryMonitor!=batteryMonitor){
		if(this->batteryMonitor)
			this->batteryMonitor->removeBatteryMonitorListener(this);
		if(batteryMonitor)
			batteryMonitor->addBatteryMonitorListener(this);
		this->batteryMonitor = batteryMonitor;
	}
}

void Controller::setHVProbe(HVProbe* hvProbe){
	if(this->hvProbe!=hvProbe){
		if(this->hvProbe)
			this->hvProbe->setMeasurementListener(nullptr);
		if(hvProbe)
			hvProbe->setMeasurementListener(this);
		this->hvProbe = hvProbe;
	}
}

void Controller::setNotificationSystem(NotificationSystem* ns){
	this->notification = ns;
}

void Controller::setLoggerSystem(){

}

void Controller::setRFDevice(){

}

void Controller::propertyChanged(
				void* source,
				unsigned short int propertyId,
				const void* oldPropery){
	if(source==this->hvProbe){
		if(propertyId==HVProbe::HVP_MEASUREMENT_PROPERTY){
			onHVProbeVoltageChanged(this->hvProbe->getAnalogValue());
		}
	}
}

void Controller::onHVProbeVoltageChanged(unsigned short int value){
	float measur = hvProbe->getMeasurement();
	float volt = hvProbe->getVoltage(AREF_VOLTAGE);

	//if(measur>1)
		//notification->notifyWarning();

	Serial.print("HVProbe Value: ");
	Serial.print(value);
	Serial.print(" Voltage: ");
	Serial.print(volt);
	Serial.print(" Measurement: ");
	Serial.print(measur);
	Serial.println( HVPROBE_UNITS );
}

void Controller::onBatteryValueChanged(
			BatteryMonitor* source, short int oldValue){

	short int value = source->getValue();
	float volts = source->getVoltage(AREF_VOLTAGE);
	short int perc = source->getPercentage();

	Serial.print("Battery Value: ");
	Serial.print(value);
	Serial.print(" Voltage: ");
	Serial.print(volts);
	Serial.print("V Percentage: ");
	Serial.print(perc);
	Serial.println( "%" );

}

void Controller::onBatteryTriggerAlarmStateChanged(
			BatteryMonitor* source, bool alarm){

	Serial.print("Battery Alarm State: ");
	Serial.print(alarm);
	Serial.println(  );

	notification->notifyWarning();
}

