/*
 * Timer.cpp
 *
 *  Created on: 9 Ιουν 2018
 *      Author: Synodiporos
 */

#include <iostream>
using namespace std;
#include "Timer.h"
#include <ctime>

Timer::Timer() {
	this->iterations = 1;
}

Timer::Timer(unsigned long interval,	unsigned int iterations){
	this->iterations = iterations;
	this->interval = interval;
}

Timer::Timer(unsigned long interval,
		unsigned int iterations, unsigned int actionId){
	this->iterations = iterations;
	this->interval = interval;
	this->actionId = actionId;
}

Timer::~Timer() {
	// TODO Auto-generated destructor stub
}

void Timer::start(){
	if(this->state!=STARTED){
		if(this->state == STOPED){
			resetIterations();
		}
		else{

		}
		updateStartTime();
		this->state = STARTED;
	}
}

void Timer::pause(){
	this->state = PAUSED;
	millisPassed = getMillisPassed();
}

void Timer::stop(){
	this->state = STOPED;
	millisPassed = 0;
	resetIterations();
}

void Timer::setActionId(unsigned int actionId){
	this->actionId = actionId;
}

unsigned int Timer::getActionId(){
	return this->actionId;
}

void Timer::setInterval(unsigned long interval){
	this->interval = interval;
}

unsigned long Timer::getInterval(){
	return this->interval;
}

void Timer::setIterations(unsigned int iterations){
	this->iterations = iterations;
}

unsigned int Timer::getIterations(){
	return this->iterations;
}

unsigned int Timer::getIterationsPerformed(){
	return this->iterPerf;
}

unsigned long Timer::getMillisPassed(){
	return clock() - this->startTime + millisPassed;
}

void Timer::setActionListener(IActionListener* listener){
	this->actionListener = listener;
}

IActionListener* Timer::getActionListener(){
	return this->actionListener;
}

void Timer::validate(){
	if(state==STARTED){
		if(getMillisPassed() >= interval){
			onAction();
		}
	}
}

void Timer::updateStartTime(){
	this->startTime = clock();
}

void Timer::resetIterations(){
	this->iterPerf = 0;
}

void Timer::notifyActionPerformed(Action* action){
	if(this->actionListener)
		this->actionListener->actionPerformed(*action);
}

void Timer::onAction(){
	iterPerf++;
	Action action = Action(this, actionId, nullptr, nullptr);
	notifyActionPerformed(&action);
	if(iterations>0 && (iterations-iterPerf)==0)
		stop();
	updateStartTime();
	millisPassed = 0;
}
