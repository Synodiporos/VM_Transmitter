/*
 * NotificationSystem.cpp
 *
 *  Created on: Jul 4, 2018
 *      Author: sgeorgiadis
 */

#include "NotificationSystem.h"

NotificationSystem::NotificationSystem(){
	initialize();
}

NotificationSystem::~NotificationSystem() {
	// TODO Auto-generated destructor stub
}

void NotificationSystem::initialize(){
	LEDTone* t11 = new LED_M1_T1;
	LEDTone* t12 = new LED_M1_T2;
	LEDTone* t13 = new LED_M1_T3;
	LEDTone* t14 = new LED_M1_T4;
	LEDTone* t15 = new LED_M1_T5;
	LEDTone* t16 = new LED_M1_T6;
	t11->setNextTone(t12);
	t12->setNextTone(t13);
	t13->setNextTone(t14);
	t14->setNextTone(t15);
	t15->setNextTone(t16);
	ledMode_active.setHeadTone(t11);
}

void NotificationSystem::notifyActive(){
	ledMode_active.play();
}

void NotificationSystem::notifyWarning(){
	ledMode_warning.play();
}

void NotificationSystem::stopNotify(){
	ledMode_active.stop();
	ledMode_warning.stop();
}

void NotificationSystem::validate(){
	ledMode_active.validate();
	ledMode_warning.validate();
}
