/*
 * Mosfet.cpp
 *
 *  Created on: Aug 3, 2018
 *      Author: sgeorgiadis
 */

#include "Mosfet.h"

Mosfet* Mosfet::instance = nullptr;

Mosfet::Mosfet() {
	// TODO Auto-generated constructor stub
	pinMode(MOSFET_PIN, OUTPUT);
	switchOFF();
}

Mosfet::~Mosfet() {
	// TODO Auto-generated destructor stub
	delete instance;
}

Mosfet* Mosfet::getInstance(){
	if(instance == nullptr)
		instance = new Mosfet();
	return instance;
}

bool Mosfet::setState(uint8_t state){
	if(this->state!=state){
		this->state = state;
		onStateChanged();
		return true;
	}
	return false;
}

uint8_t Mosfet::getState(){
	return this->state;
}

bool Mosfet::switchON(){
	return setState(MOS_STATE_ON);
}

bool Mosfet::switchOFF(){
	return setState(MOS_STATE_OFF);
}

void Mosfet::onStateChanged(){
	digitalWrite(MOSFET_PIN, getState());
}
