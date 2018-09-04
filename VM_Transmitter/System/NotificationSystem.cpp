/*
 * NotificationSystem.cpp
 *
 *  Created on: Jul 4, 2018
 *      Author: sgeorgiadis
 */
#include "Arduino.h"
#include "NotificationSystem.h"

NotificationSystem* NotificationSystem::instance = nullptr;

NotificationSystem::NotificationSystem(){
	initialize();

}

NotificationSystem::~NotificationSystem() {
	// TODO Auto-generated destructor stub
}

NotificationSystem* NotificationSystem::getInstance(){
	if(instance==nullptr){
		instance = new NotificationSystem();
	}
	return instance;
}

void NotificationSystem::initialize(){
	ledWhite.setHeadTone(LTActive);
	ledWhite.setIterations(1);
}

bool NotificationSystem::setEnabled(bool enabled){
	if(this->enable!=enabled){
		this->enable = enabled;
		return true;
	}
	return false;
}

bool NotificationSystem::isEnabled(){
	return this->enable;
}

void NotificationSystem::setHVWarningEnabled(bool enabled){
	if(!enable)
			return;
	if(isHVWarningEnabled()==enabled)
		return;
	if(enabled)
		state |= HV_WARNING;
	else
		state &= 255-HV_WARNING;
	onStateChanged(HV_WARNING);
}

void NotificationSystem::setBatteryLowEnabled(bool enabled){
	if(!enable)
			return;
	if(isBatterLowEnabled()==enabled)
			return;
	if(enabled)
		state |= BATTERY;
	else
		state &= 255-BATTERY;
	onStateChanged(BATTERY);
}

void NotificationSystem::setErrorEnabled(bool enabled){
	if(!enable)
			return;
	if(isErrorEnabled()==enabled)
			return;
	if(enabled)
		state |= ERROR;
	else
		state &= 255-ERROR;
	onStateChanged(ERROR);
}

void NotificationSystem::setActiveEnabled(bool enabled){
	if(!enable)
		return;
	if(isActiveEnabled()==enabled)
		return;
	if(enabled)
		state |= ACTIVE;
	else
		state &= 255-ACTIVE;
	onStateChanged(ACTIVE);
}

void NotificationSystem::setConnectionLostEnabled(bool enabled){
	if(!enable)
			return;
	if(isConnectionLostEnabled()==enabled)
		return;
	if(enabled)
		state |= CONNECTION_LOST;
	else
		state &= 255-CONNECTION_LOST;

	onStateChanged(ACTIVE);
}

void NotificationSystem::setTranferDataEnabled(bool enabled){
	if(!enable)
		return;
	if(enabled)
		state |= TRANSFER;
	else
		state &= 255-TRANSFER;

	onStateChanged(ACTIVE);
}

bool NotificationSystem::isHVWarningEnabled(){
	return bitRead(state, 7) == 1;
}

bool NotificationSystem::isBatterLowEnabled(){
	return bitRead(state, 6) == 1;
}

bool NotificationSystem::isErrorEnabled(){
	return bitRead(state, 5) == 1;
}

bool NotificationSystem::isConnectionLostEnabled(){
	return bitRead(state, 4) == 1;
}

bool NotificationSystem::isTranferDataEnabled(){
	return bitRead(state, 3) == 1;
}

bool NotificationSystem::isActiveEnabled(){
	return bitRead(state, 2) == 1;
}

void NotificationSystem::startNotify(){
	validateChanges();
}

void NotificationSystem::stopNotify(){
	ledWhite.stop();
	ledRed.stop();
	//ledBlue.stop();
	player.stop();
}

void NotificationSystem::validateChanges(){
	if(isHVWarningEnabled()){
		//Enable HV Warning only
		ledRed.setHeadTone(LTHVWarning);
		ledRed.setIterations(0);
		ledRed.play();

		player.setHeadTone(BTHVWarning);
		player.setIterations(0);
		//player.play();

		ledWhite.stop();

	}else {
		player.stop();
		ledRed.stop();

		if(isConnectionLostEnabled()){
			//Enabled Connection Error
			ledRed.setHeadTone(LTConnLost);
			ledRed.setIterations(1);
			ledRed.play();
		}
		else if(isBatterLowEnabled()){
			ledRed.setHeadTone(LTBatteryWarning);
			ledRed.setIterations(1);
			ledRed.play();
		}
		else{

		}

		if(isActiveEnabled()){
			ledWhite.play();
		}
	}
}

void NotificationSystem::onStateChanged(byte change){
	validateChanges();

	if(change>=32){
		//Serial.println("RED change");
		if(change>=state){

		}
	}
	else if(change>=8){
		//Serial.println(F("BLUE change"));
		byte state = this->state || 11100000;
		if(change>=state){

		}
	}
	else if(change>=4){
		//Serial.println(F("WHITE change"));
		byte state = this->state || 11111000;
		if(change>=state){

		}
	}
}

void NotificationSystem::validate(){
	if(!enable)
		return;
	player.validate();
	ledWhite.validate();
	ledRed.validate();
	//ledBlue.validate();
}

void NotificationSystem::setMelody(BuzzerTone* tone){
	if(tone==nullptr){
		this->player.stop();
	}
	else{
		this->player.setHeadTone(tone);
		this->player.play();
	}
}
