/*
 * AnalogInput.cpp
 *
 *  Created on: Apr 20, 2018
 *      Author: sgeorgiadis
 */

#include "Arduino.h"
#include "AnalogInput.h"

AnalogInput::AnalogInput(uint8_t pinNumber)
	: _pinNumber(pinNumber){
	readings = new unsigned short int[1];
	clearRecordsTable();
}

AnalogInput::AnalogInput(uint8_t pinNumber, uint8_t spv)
	: _pinNumber(pinNumber){
	readings = new unsigned short int[spv];
	this->spv = spv;
	clearRecordsTable();
}

AnalogInput::~AnalogInput() {
	// TODO Auto-generated destructor stub
}

void AnalogInput::clearRecordsTable(){
	for (unsigned int thisReading = 0;
			thisReading < spv; thisReading++) {
		readings[thisReading] = 0;
	}
	total = 0;
	readIndex = 0;
	flag = 0;
}

uint8_t AnalogInput::getPinNumber(){
	return this->_pinNumber;
}
unsigned short int AnalogInput::getAnalogValue(){
	return this->_analogValue;
}

void AnalogInput::setPropertyListener(IPropertyListener* listener){
	this->_listener = listener;
}

IPropertyListener* AnalogInput::getPropertyListener(){
	return this->_listener;
}

void AnalogInput::notifyPropertyChanged(unsigned long old){
	if(_listener){
		_listener->propertyChanged(this, PROPERTY_ANALOG_VALUE,
				&old);
	}
}

void AnalogInput::validate(){
	// subtract the last reading:
	total = total - readings[readIndex];
	// read from the sensor:
	readings[readIndex] = analogRead(_pinNumber);
	// add the reading to the total:
	total = total + readings[readIndex];
	// advance to the next position in the array:
	readIndex = readIndex + 1;

	int count = readIndex;
	if(flag==1)
		count = spv;

	// if we're at the end of the array...
	if (readIndex >= spv) {
		// ...wrap around to the beginning:
		readIndex = 0;
		flag = 1;
	}

	// calculate the average:
	unsigned short int average = total / count;

	Serial.print("total: ");
	Serial.print(total);
	Serial.print("  count: ");
	Serial.print(count);
	Serial.print(" average: ");
	Serial.println(average);

	//Check if average value has changed
	if(average != getAnalogValue()){
		unsigned short int old = getAnalogValue();
		notifyPropertyChanged(old);
		//Update the analogeValue value
		_analogValue = average;
		analogValueChanged(old, average);
	}
}

void AnalogInput::analogValueChanged(
		unsigned short int analogValue, unsigned short int old){

}
