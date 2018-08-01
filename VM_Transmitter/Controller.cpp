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
		notification->setActiveEnabled(true);
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

	Serial.print(F("HVProbe Value: "));
	Serial.print(value);
	Serial.print(F(" Voltage: "));
	Serial.print(volt);
	Serial.print(F(" Measurement: "));
	Serial.print(measur);
	Serial.println( HVPROBE_UNITS );

	/*byte b1 = lowByte(value);
	byte b2 = highByte(value);
	Serial.print("HVProbe Value: ");
	Serial.print(value);
	Serial.print(" HB: ");
	Serial.println(b2, BIN);
	Serial.print(" LB: ");
	Serial.println(b1, BIN);*/

}

void Controller::onBatteryValueChanged(
			BatteryMonitor* source, short int oldValue){

	short int value = source->getValue();
	float volts = source->getVoltage(AREF_VOLTAGE);
	short int perc = source->getPercentage();

	Serial.print(F("Battery Value: "));
	Serial.print(value);
	Serial.print(F(" Voltage: "));
	Serial.print(volts);
	Serial.print(F("V Percentage: "));
	Serial.print(perc);
	Serial.println( "%" );
}

void Controller::onBatteryTriggerAlarmStateChanged(
			BatteryMonitor* source, bool alarm){

	Serial.print(F("Battery Alarm State: "));
	Serial.print(alarm);
	Serial.println(  );

	//notification->setBatteryLowEnabled(true);
}

