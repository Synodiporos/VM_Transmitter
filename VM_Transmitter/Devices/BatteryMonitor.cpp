/*
 * BatteryMonitor.cpp
 *
 *  Created on: Jul 3, 2018
 *      Author: sgeorgiadis
 */

#include "BatteryMonitor.h"
#include "Arduino.h"

BatteryMonitor::BatteryMonitor() {
	initialize();
}

BatteryMonitor::~BatteryMonitor() {
	// TODO Auto-generated destructor stub
}

void BatteryMonitor::initialize(){
	//analog.setPropertyListener(this);
	timer.setActionListener(this);
	timer.start();
}

uint8_t BatteryMonitor::getPercentage(){
	return MathUtil::mapRange(analog.getAnalogValue(),
			814, 1023, (short int)0, (short int)100);
}

float BatteryMonitor::getVoltage(){
	return MathUtil::map(analog.getAnalogValue(),
				0, 1023, 0, BATTM_MAX_RANGE);
}

void BatteryMonitor::propertyChanged(
				void* source,
				unsigned short int propertyId,
				const void* oldPropery){

}

void BatteryMonitor::actionPerformed(Action action){
	unsigned short int act =
			*(unsigned short int*)action.getContainer();
	if(act==Timer::TIMER_TIC){
		analog.validate();
	}
	else if(act==Timer::TIMER_STOP){
		//Serial.println("TIMER STOP ");
		unsigned short int value = analog.getAnalogValue();
		if(value!=oldValue){

			Serial.print("Battery: ");
			Serial.print(value);
			Serial.print(" - ");
			Serial.print(getVoltage());
			Serial.print("V - ");
			Serial.print(getPercentage());
			Serial.println("%");

			oldValue = value;
		}
		timer.start();
	}
}

void BatteryMonitor::validate(){
	timer.validate();
}
