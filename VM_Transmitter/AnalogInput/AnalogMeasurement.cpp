/*
 * AnalogMeasurement.cpp
 *
 *  Created on: Jun 21, 2018
 *      Author: sgeorgiadis
 */

#include "AnalogMeasurement.h"

AnalogMeasurement::AnalogMeasurement(uint8_t pinNumber)
	: AnalogInput(pinNumber){

}

AnalogMeasurement::AnalogMeasurement(
		uint8_t pinNumber, uint8_t spv)
	: AnalogInput(pinNumber, spv){

}

AnalogMeasurement::AnalogMeasurement(
		uint8_t pinNumber, uint8_t spv,
			float min, float max, char* units)
	: AnalogInput(pinNumber, spv){
	  setLimits(min, max);
	  setUnits(units);
}

AnalogMeasurement::~AnalogMeasurement() {
	// TODO Auto-generated destructor stub
}

void AnalogMeasurement::setLimits(float min, float max){
	this->min = min;
	this->max = max;
}

float AnalogMeasurement::getMin(){
	return min;
}

float AnalogMeasurement::getMax(){
	return max;
}

void AnalogMeasurement::setUnits(char* units){
	this->units = units;
}

char* AnalogMeasurement::getUnits(){
	return this->units;
}

float AnalogMeasurement::getMeasurement(){
	float res = map(getAnalogValue(), min, max);
	return res;
}

long AnalogMeasurement::map(long x, long out_min, long out_max){
	return (x - 0) * (out_max - out_min) / (1023 - 0) + out_min;
}

