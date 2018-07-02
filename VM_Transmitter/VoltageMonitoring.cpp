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

}

VoltageMonitoring::~VoltageMonitoring() {
	// TODO Auto-generated destructor stub
}

void VoltageMonitoring::initialize(){
	probe.setUnit(HVPROBE_UNITS);
	probe.setRange(HVPROBE_MIN_RANGE, HVPROBE_MAX_RANGE);
	probe.setMeasurementListener(this);
}

void VoltageMonitoring::propertyChanged(
				void* source,
				unsigned short int propertyId,
				const void* oldPropery){
	if(propertyId==HVProbe::MEASUREMENT_PROPERTY){
		float measur = probe.getMeasurement();

		Serial.print("Measurement: ");
		Serial.print(measur);
		Serial.println(probe.getUnits());
	}
}

void VoltageMonitoring::validate(){
	probe.validate();
}
