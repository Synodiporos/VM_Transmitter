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

uint8_t SurgeMonitor::getState(){
	return this->state;
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
	return getState() == SM_STATE_CHARGING;
}

//Measurement in ADC
void SurgeMonitor::setMeasurement(unsigned int measurement){
	if(measurement>SM_SURGE_MIN){
		if(getState()==SM_STATE_DISCHARGED){
			onCharging();
		}
		if(measurement>maxMeasure)
				setMaxMeasurement(measurement);
	}
	else if( measurement<SM_SURGE_MIN-2)
		onDischarged();
}

void SurgeMonitor::validate(){
	if(getState()==SM_STATE_CHARGING){
		if(millis()-timeCharge>=SM_CHARGE_INTERVAL){
			onCharged();
			timeCharge = millis();
		}
	}
}

void SurgeMonitor::setState(uint8_t state){
	if(this->state!=state){
		this->state = state;
		notifyActionListener();
	}
}

void SurgeMonitor::setMaxMeasurement(unsigned int max){
	if(this->maxMeasure!=max){
		this->maxMeasure = max;

		if(count<NOR){
			//KEEP RECORD
			float secs = (float)(millis() - time)/1000;
			unsigned int aps =
					((float)(max-initMeasure)/secs)*10;

			buf[i] = aps;
			i++;
			if(i==NOM)
				i=0;
			/*Serial.print("======================= MAX i=");
			Serial.print(i);
			Serial.print(" slope: ");
			Serial.println(aps);*/
		}

		if(count<=254)
			count++;
		timeCharge = millis();
	}
}

void SurgeMonitor::clearBuffer(){
	for(int i=0; i<NOM; i++){
		buf[i] = 0;
	}
	this->i = 0;
}

void SurgeMonitor::onCharging(){
	setState(SM_STATE_CHARGING);
	this->initMeasure = maxMeasure;
	this->time = millis();
	//Serial.println("&&& OnCharging ");
}

void SurgeMonitor::onCharged(){
	setState(SM_STATE_CHARGED);
}

void SurgeMonitor::onDischarged(){


	//notifyActionListener();

/*
	Serial.print("BUFFER: ");
	for(int i=0; i<NOM; i++){
		Serial.print( buf[i]);
		Serial.print( ", ");
	}
	Serial.println();*/

	setState(SM_STATE_DISCHARGED);
	this->count = 0;
	this->maxMeasure = 0;
	this->initMeasure = 0;
	clearBuffer();
}

void SurgeMonitor::notifyActionListener(){
	if(this->actionListener){
		Surge surge;
		if(getState()==SM_STATE_DISCHARGED ||
				getState()==SM_STATE_CHARGED){
			int ii = (i);
			if(count<5)
				ii = 0;
			if(ii==NOM)
				ii=0;

			surge.datetime = UnixTime::getUnixTime();
			surge.device = getDevice();
			surge.charge = maxMeasure;
			surge.slope = buf[ii];
		}

		Action action =
				Action(this, ON_SM_STATE_CHANGED, nullptr, &surge);
		actionListener->actionPerformed(action);
	}
}

