/*
 * CMDStartUp.cpp
 *
 *  Created on: 30 Ιουλ 2018
 *      Author: Synodiporos
 */

#include "CMDStartUp.h"

CMDStartUp::CMDStartUp() : CMD(){
	// TODO Auto-generated constructor stub
}

CMDStartUp::~CMDStartUp() {
	// TODO Auto-generated destructor stub
}

uint8_t CMDStartUp::onExecute(){
	digitalWrite(LED_WHITE_PIN, HIGH);
	digitalWrite(LED_RED_PIN, HIGH);
	digitalWrite(LED_BLUE_PIN, HIGH);

	this->timer.start();
	return RES_ONPROGRESS;
}

void CMDStartUp::validate(){
	if(this->timer.getState() == Timer::TIMER_STOP){

		digitalWrite(LED_WHITE_PIN, LOW);
		digitalWrite(LED_RED_PIN, LOW);
		digitalWrite(LED_BLUE_PIN, LOW);
		CMD::onCompleted();
	}
}
