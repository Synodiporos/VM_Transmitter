/*
 * Probe.cpp
 *
 *  Created on: 8 Αυγ 2018
 *      Author: Synodiporos
 */

#include "Probe.h"

Probe::Probe(uint8_t pin, unsigned int rate) :
	pin(pin), rate(rate){
}

Probe::~Probe() {
	// TODO Auto-generated destructor stub
}

void Probe::setEnabled(bool enabled){
	this->enabled = enabled;
}

bool Probe::isEnabled(){
	return this->enabled;
}

void Probe::setFrequency(float frequency){
	this->filter.setFrequency(frequency);
}

void Probe::setSamplingRate(unsigned int rate){
	this->rate = rate;
}

float Probe::voltage(float vref, float offset){
	return (this->getMeasurement()*vref)/1023 + offset;
}

unsigned int Probe::getMeasurement(){
	return this->measurement;
}

void Probe::setMeasurement(unsigned int measurement){
	if(this->measurement!=measurement){
		unsigned int old = this->measurement;
		this->measurement = measurement;
		/*Serial.print("Probe: ");
		Serial.print( measurement);
		Serial.print(" Voltage=");
		Serial.println( voltage(AREF_VOLTAGE, 0) );*/
		notifyMeasurementChanged(old);
	}
}

void Probe::setListener(IPropertyListener* listener){
	this->listener = listener;
}

IPropertyListener* Probe::getListener(){
	return this->listener;
}

void Probe::validate(){
	if(isEnabled() && (millis()-time) >= rate){
		setMeasurement(
				filter.input(analogRead(pin)));
		time = millis();
	}

	/*if(isEnabled() && (millis()-time) >= (count*rate/div)){
			if(count < div){
				filter.input(analogRead(pin));
				count++;
			}
			else{
				setMeasurement(
						filter.input(analogRead(pin)));
				count=0;
				time = millis();
			}
		}*/
}

void Probe::notifyMeasurementChanged(unsigned int oldMeas){
	if(this->listener){
		listener->propertyChanged(this, 0, &oldMeas);
	}
}
