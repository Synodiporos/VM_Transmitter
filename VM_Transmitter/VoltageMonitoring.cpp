/*
 * VoltageMonitoring.cpp
 *
 *  Created on: Jul 2, 2018
 *      Author: sgeorgiadis
 */

#include "Arduino.h"
#include "VoltageMonitoring.h"

VoltageMonitoring::VoltageMonitoring() {
	// TODO Auto-generated constructor stub
	initialize();
}

VoltageMonitoring::~VoltageMonitoring() {
	// TODO Auto-generated destructor stub
}

void VoltageMonitoring::initialize(){
	probe.setMeasurementListener(this);
}

void VoltageMonitoring::propertyChanged(
				void* source,
				unsigned short int propertyId,
				const void* oldPropery){

	if(propertyId==HVProbe::MEASUREMENT_PROPERTY){
		short int value = probe.getAnalogValue();
		float measur = probe.getMeasurement();
		float volt = probe.getVoltage();

		Serial.print("AnalogValue: ");
		Serial.print(value);
		Serial.print(" Voltage: ");
		Serial.print(volt);
		Serial.print(" Measurement: ");
		Serial.print(measur);
		Serial.println( HVPROBE_UNITS );
	}
}

void VoltageMonitoring::validate(){
	probe.validate();
}

void VoltageMonitoring::validateTimer(){
	probe.validateTimer();
}
