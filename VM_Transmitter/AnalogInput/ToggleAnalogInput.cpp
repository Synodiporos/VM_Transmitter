/*
 * ToggleAnalogInput.cpp
 *
 *  Created on: Apr 20, 2018
 *      Author: sgeorgiadis
 */
#include "Arduino.h"
#include "ToggleAnalogInput.h"
#include <string>

ToggleAnalogInput::ToggleAnalogInput(uint8_t pinNumber) :
	AnalogInput(pinNumber){
}

ToggleAnalogInput::ToggleAnalogInput(uint8_t pinNumber, uint8_t spv) :
	AnalogInput(pinNumber, spv){
}

ToggleAnalogInput::ToggleAnalogInput(uint8_t pinNumber, uint8_t spv,
			unsigned short int switchValue):
				AnalogInput(pinNumber, spv){
	this->switchValue = switchValue;
}

ToggleAnalogInput::ToggleAnalogInput(uint8_t pinNumber, uint8_t spv,
			unsigned short int switchValue,
			unsigned short int hysterisis):
				AnalogInput(pinNumber, spv){
	this->switchValue = switchValue;
	this->hysterisis = hysterisis;
}

ToggleAnalogInput::~ToggleAnalogInput() {
	// TODO Auto-generated destructor stub
}

bool ToggleAnalogInput::getToggleState(){
	return state;
}

void ToggleAnalogInput::setSwitchValue(unsigned short int switchValue){
	this->switchValue = switchValue;
}

unsigned short int ToggleAnalogInput::getSwitchValue(){
	return this->switchValue;
}

void ToggleAnalogInput::setHysterisis(unsigned short int hysterisis){
	this->hysterisis = hysterisis;
}

unsigned short int ToggleAnalogInput::getHysterisis(){
	return this->hysterisis;
}

void ToggleAnalogInput::setStateListener(IStateListener * listener){
	this->_stateListener = listener;
}

IStateListener* ToggleAnalogInput::getStateListener(){
	return this->_stateListener;
}

void ToggleAnalogInput::notifyPropertyChanged(unsigned long old){
	AnalogInput::notifyPropertyChanged(old);
	/*Serial.print("AnalogValue: ");
	Serial.print(getAnalogeValue());
	Serial.print(" Toggle: ");
	Serial.println(state);*/

	if(!this->state){
		if(this->_analogValue >= (this->switchValue + this->hysterisis)){
			this->state = true;
			notifyToggleStateChanged();
		}
	}
	else{
		if(this->_analogValue <= (this->switchValue)){
			this->state = false;
			notifyToggleStateChanged();
		}
	}
}

void ToggleAnalogInput::notifyToggleStateChanged(){
	if(_stateListener!=0){
		char c = getPinNumber();
		State* state = new State(this, c, nullptr);
		_stateListener->stateChanged(state);
	}
}
