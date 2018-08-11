/*
 * HVProbe.cpp
 *
 *  Created on: Jul 2, 2018
 *      Author: sgeorgiadis
 */

#include "HVProbe.h"
#include "Arduino.h"

HVProbe::HVProbe(uint8_t pinNumber):
	AnalogInput(pinNumber){
	initialize();
}

HVProbe::HVProbe(uint8_t pinNumber, uint8_t spv) :
	AnalogInput(pinNumber, spv){
	initialize();
}

HVProbe::HVProbe(uint8_t pinNumber, uint8_t spv,
			unsigned short int period) :
	AnalogInput(pinNumber, spv){
		initialize();
		timer.setInterval(period);
}

HVProbe::~HVProbe() {
	// TODO Auto-generated destructor stub
}

void HVProbe::initialize(){
	timer.setActionListener(this);
}

void HVProbe::startRecord(){
	timer.start();
}

void HVProbe::pauseRecord(){
	timer.pause();
}

void HVProbe::stopRecord(){
	timer.stop();
	clearRecordsTable();
}

float HVProbe::getMeasurement(){
	return MathUtil::mapRange(getAnalogValue(),
			0, 1023, HVPROBE_MIN_MEAS_RANGE, HVPROBE_MAX_MEAS_RANGE);
}

float HVProbe::getVoltage(float VREF){
	return MathUtil::map(getAnalogValue(),
			0, 1023, 0, VREF);
}

void HVProbe::actionPerformed(Action action){
	short int actionId = action.getActionId();
	unsigned short int measurement = getAnalogValue();
	//if(actionId==0){
		if(measurement!=oldAnalogValue){
			notifyMeasurementChanged();
			oldAnalogValue = measurement;
		}
	//}
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
				this, HVP_MEASUREMENT_PROPERTY, &oldAnalogValue);
}

void HVProbe::analogValueChanged(
					unsigned short int analogValue,
					unsigned short int old){

}

void HVProbe::validate(){
	AnalogInput::validate();
	timer.validate();
}

