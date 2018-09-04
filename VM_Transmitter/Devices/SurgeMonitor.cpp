/*
 * SurgeMonitor.cpp
 *
 *  Created on: 4 Σεπ 2018
 *      Author: Synodiporos
 */

#include "SurgeMonitor.h"

SurgeMonitor::SurgeMonitor() {
	// TODO Auto-generated constructor stub
	clearBuffer();
}

SurgeMonitor::~SurgeMonitor() {
	// TODO Auto-generated destructor stub
}

void SurgeMonitor::setDevice(uint8_t device){
	if(this->device!=device)
		this->device = device;
}

uint8_t SurgeMonitor::getDevice(){
	return this->device;
}

bool SurgeMonitor::isCharging(){
	return this->state==1;
}

void SurgeMonitor::setMeasurement(unsigned int measurement){

	if(measurement>SM_SURGE_MIN){
		if(!isCharging()){
			onCharging();
		}
		if(measurement>maxMeasure)
				setMaxMeasurement(measurement);
	}
	else if( measurement<SM_SURGE_MIN-2 && isCharging() )
		onDischarged();
}

void SurgeMonitor::validate(){

}

void SurgeMonitor::setMaxMeasurement(unsigned int max){
	if(this->maxMeasure!=max){
		this->maxMeasure = max;

		float secs = (float)(millis() - time)/1000;
		unsigned short int aps =
				((float)(max-SM_SURGE_MIN)/secs)*100;

		buf[i] = aps;

		Serial.print("&&& Probe Max: ");
		Serial.print( maxMeasure);
		Serial.print(" time: ");
		Serial.print( secs);

		int ii = (i+1);
		if(ii==NOM)
			ii=0;
		Serial.print(" i: ");
		Serial.print( i);
		Serial.print(" ii: ");
		Serial.println( ii);

		i++;
		if(i==NOM)
			i=0;
	}
}

void SurgeMonitor::clearBuffer(){
	for(int i=0; i<NOM; i++){
		buf[i] = 0;
	}
	this->i = 0;
}

void SurgeMonitor::onCharging(){
	this->state = 1;
	this->time = millis();
	Serial.println("&&& OnCharging ");
}

void SurgeMonitor::onDischarged(){
	this->state = 0;
	this->maxMeasure = 0;
	Serial.println("&&& OnDischarging");

	int ii = (i);
	if(ii==NOM)
		ii=0;
	float slope = (float)buf[ii]/100;

	Serial.print(" Buffer: ");
	for(int i=0; i<NOM; i++){
		Serial.print(buf[i]);
		Serial.print(", ");
	}

	Serial.print(" Slope: ");
	Serial.print(slope);
	Serial.print(" aps");
	Serial.println();

	clearBuffer();
}

