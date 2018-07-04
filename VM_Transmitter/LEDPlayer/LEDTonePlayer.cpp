/*
 * LEDTonePlayer.cpp
 *
 *  Created on: Jul 4, 2018
 *      Author: sgeorgiadis
 */

#include <Arduino.h>
#include "LEDTonePlayer.h"

LEDTonePlayer::LEDTonePlayer(int8_t pinNumber) :
	_pinNumber(pinNumber){
	// TODO Auto-generated constructor stub
	initialize();
}

LEDTonePlayer::LEDTonePlayer(int8_t pinNumber, LEDTone* headTone) :
	_pinNumber(pinNumber), _headTone(headTone){
	// TODO Auto-generated constructor stub
	initialize();
}

LEDTonePlayer::LEDTonePlayer(int8_t pinNumber, LEDTone* headTone, short int iterations) :
	_pinNumber(pinNumber), _headTone(headTone){
	this->setIterations(iterations);
	initialize();
}

LEDTonePlayer::~LEDTonePlayer() {
	// TODO Auto-generated destructor stub
}

void LEDTonePlayer::initialize(){
	int8_t pin = getPinNumber();
	if(pin>0)
		pinMode(pin, OUTPUT);
}

int8_t LEDTonePlayer::getPinNumber(){
	return this->_pinNumber;
}

void LEDTonePlayer::setIterations(short int iterations){
	this->_iterations = iterations;
	this->_performedIter = 0;
}

short int LEDTonePlayer::getIterations(){
	return this->_iterations;
}

void LEDTonePlayer::setHeadTone(LEDTone* headTone){
	this->_headTone = headTone;
}

uint8_t LEDTonePlayer::getState(){
	return this->_state;
}

LEDTone* LEDTonePlayer::getHeadTone(){
	return this->_headTone;
}

LEDTone* LEDTonePlayer::getCurrentTone(){
	return this->_currentTone;
}

void LEDTonePlayer::play(){
	if(_headTone){
		//Serial.println("Buzzer Melody Start");
		if(_state==0){
			_interval = 0;
			_performedIter = 0;
		}
	}
	_millis = millis();
	this->_state = 2;
	playCurrentTone();
}

void LEDTonePlayer::pause(){
	this->_state = 1;
	//Serial.println("Buzzer Melody Paused");
	_interval = millis()-_millis;
	noTone(_pinNumber);
}

void LEDTonePlayer::stop(){
	//Serial.println("Buzzer Melody stop");
	this->_state = 0;
	_currentTone = _headTone;
	_interval = 0;
	noTone(_pinNumber);
}

void LEDTonePlayer::playNextTone(){
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
		if(_performedIter==-1 || _performedIter<_iterations)	{
			_currentTone = _headTone;
			playCurrentTone();
		}
		//There are NO remaining iterations
		else{
			_currentTone = _currentTone->getNextTone();
			stop();
		}
	}
}

void LEDTonePlayer::playCurrentTone(){
	playTone(_currentTone);
}

void LEDTonePlayer::resumeFromCurrent(){

}

void LEDTonePlayer::playTone(LEDTone* _tone){
	/*Serial.print("Play Tone: ");
	Serial.print(freq);
	Serial.print(" duration: ");
	Serial.print(_tone->getDuration());
	Serial.print(" interval: ");
	Serial.println(_interval);*/
	if(!_tone)
			return;
	uint8_t freq = _tone->getFrequency();
	analogWrite(_pinNumber, freq);
}

void LEDTonePlayer::validate(){
	if(_state==2){
		//_interval = (millis() - _millis);
		if((millis()-_millis + _interval) >= _currentTone->getDuration()){
			playNextTone();
		}
	}
	//_millis = millis();
}
