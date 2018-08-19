/*
 * BuzzerMelody.cpp
 *
 *  Created on: 22 Απρ 2018
 *      Author: Synodiporos
 */

#include <Arduino.h>
#include "BuzzerMelody.h"

BuzzerMelody::BuzzerMelody(uint8_t pinNumber) :
	_pinNumber(pinNumber){
	// TODO Auto-generated constructor stub
	initialize();
}

BuzzerMelody::BuzzerMelody(uint8_t pinNumber, BuzzerTone* headTone) :
	_pinNumber(pinNumber), _headTone(headTone){
	// TODO Auto-generated constructor stub
	initialize();
}

BuzzerMelody::BuzzerMelody(uint8_t pinNumber, BuzzerTone* headTone, short int iterations) :
	_pinNumber(pinNumber), _headTone(headTone),
	_iterations(iterations){
	initialize();
}

BuzzerMelody::~BuzzerMelody() {
	// TODO Auto-generated destructor stub
}

void BuzzerMelody::initialize(){
	_currentTone = _headTone;
	int8_t pin = getPinNumber();
	if(pin>0)
		pinMode(pin, OUTPUT);
}

uint8_t BuzzerMelody::getPinNumber(){
	return this->_pinNumber;
}

void BuzzerMelody::setIterations(short int iterations){
	this->_iterations = iterations;
}

short int BuzzerMelody::getIterations(){
	return this->_iterations;
}

void BuzzerMelody::setHeadTone(BuzzerTone* headTone){
	this->_headTone = headTone;
	_currentTone = _headTone;
}

uint8_t BuzzerMelody::getState(){
	return this->_state;
}

BuzzerTone* BuzzerMelody::getHeadTone(){
	return this->_headTone;
}

BuzzerTone* BuzzerMelody::getCurrentTone(){
	return this->_currentTone;
}

void BuzzerMelody::play(){
	if(_headTone && _state!=2){
		//Serial.println("Buzzer Melody Start");
		if(_state==0){
			_interval = 0;
			_performedIter = 0;
		}
		_millis = millis();
		this->_state = 2;
		playCurrentTone();
	}
}

void BuzzerMelody::pause(){
	this->_state = 1;
	//Serial.println("Buzzer Melody Paused");
	_interval = millis()-_millis;
	noTone(_pinNumber);
}

void BuzzerMelody::stop(){
	//Serial.println("Buzzer Melody stop");
	this->_state = 0;
	_currentTone = _headTone;
	_interval = 0;
	noTone(_pinNumber);
}

void BuzzerMelody::playNextTone(){
	_interval = 0;
	_millis = millis();
	//Current Tone has next tone
	if(_currentTone->hasNext()){
		_currentTone = _currentTone->getNextTone();
		playCurrentTone();
	}
	//Current Tone has no next tone
	else{
		//There are remaining iterations to be performed
		_performedIter++;
		if(_iterations==0 || _performedIter<_iterations){
			_currentTone = _headTone;
			playCurrentTone();
		}
		//There are NO remaining iterations
		else{
			_currentTone = _currentTone->getNextTone();
			stop();
			if(_performedIter==_iterations)
						_performedIter=0;
		}
	}
}

void BuzzerMelody::playCurrentTone(){
	playTone(_currentTone);
}

void BuzzerMelody::resumeFromCurrent(){

}

void BuzzerMelody::playTone(BuzzerTone* _tone){
	/*Serial.print("Play Tone: ");
	Serial.print(freq);
	Serial.print(" duration: ");
	Serial.print(_tone->getDuration());
	Serial.print(" interval: ");
	Serial.println(_interval);*/
	if(!_tone)
			return;
	unsigned short int freq = _tone->getFrequency();
	if(freq>0)
		tone(_pinNumber, freq);
	else
		noTone(_pinNumber);
}

void BuzzerMelody::validate(){
	if(_state==2){
		//_interval = (millis() - _millis);
		if((millis()-_millis + _interval) >=
				_currentTone->getDuration()){
			playNextTone();
		}
	}
	//_millis = millis();
}
