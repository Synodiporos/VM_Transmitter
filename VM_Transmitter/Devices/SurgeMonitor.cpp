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

void SurgeMonitor::setActionListener(IActionListener* listener){
	this->actionListener = listener;
}

IActionListener* SurgeMonitor::getActionListener(){
	return this->actionListener;
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
		unsigned int aps =
				((float)(max-initMeasure)/secs)*10;

		buf[i] = aps;
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
	this->initMeasure = maxMeasure;
	this->time = millis();
	//Serial.println("&&& OnCharging ");
}

void SurgeMonitor::onDischarged(){
	int ii = (i);
	if(ii==NOM)
		ii=0;

	unsigned int data[3];
	data[0] = getDevice();
	data[1] = maxMeasure;
	data[2] = buf[ii];

	notifyActionListener(data);
/*
	Serial.print("BUFFER: ");
	for(int i=0; i<NOM; i++){
		Serial.print( buf[i]);
		Serial.print( ", ");
	}
	Serial.println();*/

	this->state = 0;
	this->maxMeasure = 0;
	this->initMeasure = 0;
	clearBuffer();
}

void SurgeMonitor::notifyActionListener(unsigned int data[3]){
	if(this->actionListener){
		Action action =
				Action(this, ON_SURGE_APPLIED, nullptr, data);
		actionListener->actionPerformed(action);
	}
}

