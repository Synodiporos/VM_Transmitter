/*
 * BuzzerTone.cpp
 *
 *  Created on: 29 Μαρ 2018
 *      Author: Synodiporos
 */

#include "BuzzerTone.h"

BuzzerTone::BuzzerTone(unsigned short int frequency, unsigned short int duration) {
	setFrequency(frequency);
	setDuration(duration);
}

BuzzerTone::BuzzerTone(unsigned short int frequency, unsigned short int duration,
			BuzzerTone* next){
	setFrequency(frequency);
	setDuration(duration);
	setNextTone(next);
}

BuzzerTone::~BuzzerTone() {
	delete this->next;
}

void BuzzerTone::setFrequency(unsigned short int frequency){
	this->frequency = frequency;
}

unsigned short int BuzzerTone::getFrequency(){
	return this->frequency;
}

unsigned short int BuzzerTone::getDuration(){
	return this->duration;
}

void BuzzerTone::setDuration(unsigned short int duration){
	this->duration = duration;
}

void BuzzerTone::setNextTone(BuzzerTone* next){
	this->next = next;
}

BuzzerTone* BuzzerTone::getNextTone(){
	return this->next;
}

bool BuzzerTone::hasNext(){
	return this->next!=0;
}
