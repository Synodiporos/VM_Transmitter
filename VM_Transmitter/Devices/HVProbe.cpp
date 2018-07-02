/*
 * HVProbe.cpp
 *
 *  Created on: Jul 2, 2018
 *      Author: sgeorgiadis
 */

#include "HVProbe.h"


HVProbe::HVProbe(uint8_t pinNumber):
	AnalogInput(pinNumber){

}

HVProbe::HVProbe(uint8_t pinNumber, uint8_t spv) :
	AnalogInput(pinNumber, spv){

}

HVProbe::~HVProbe() {
	// TODO Auto-generated destructor stub
}

void HVProbe::initialize(){
	timer.setActionListener(this);
}

float HVProbe::getMeasurement(){
	return MathUtil::map(getAnalogValue(),
			minValue, maxValue, 0, 1023);
}
void HVProbe::setUnit(char* units){
	this->units = units;
}

char* HVProbe::getUnits(){
	return this->units;
}

void HVProbe::setRange(float min, float max){
	this->minValue = min;
	this->maxValue = max;
}

void HVProbe::actionPerformed(Action action){
	short int actionId = action.getActionId();
	unsigned short int measurement = getAnalogValue();
	if(actionId==MEASUREMENT_CHANGED){
		if(measurement!=oldAnalogValue){
			notifyMeasurementChanged();
		}
	}
}

void HVProbe::setMeasurementListener(IPropertyListener* listener){
	this->measurementListener = listener;
}

IPropertyListener* HVProbe::getMeasurementListener(){
	return this->measurementListener;
}

void HVProbe::notifyMeasurementChanged(){
	if(measurementListener)
		measurementListener->propertyChanged(
				this, MEASUREMENT_PROPERTY, &oldAnalogValue);
}

void HVProbe::analogValueChanged(
					unsigned short int analogValue,
					unsigned short int old){
	timer.validate();
}

void HVProbe::validate(){
	AnalogInput::validate();
}
