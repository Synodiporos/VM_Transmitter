/*
 * RFTransceiver.cpp
 *
 *  Created on: Jul 6, 2018
 *      Author: sgeorgiadis
 */

#include "RFTransceiver.h"

RFTransceiver* RFTransceiver::instance = nullptr;

RFTransceiver::~RFTransceiver() {
	// TODO Auto-generated destructor stub
}

RFTransceiver::RFTransceiver() {
	// TODO Auto-generated constructor stub
	//initialize();
}

RFTransceiver* RFTransceiver::getInstance(){
	if(instance==nullptr){
		instance = new RFTransceiver();
	}
	return instance;
}

//MASTER
void RFTransceiver::initialize(RF24* radio){
	this->radio = radio;
	if(radio->begin()){
		radio->setRetries(15, 15);
		radio->disableDynamicPayloads();
		radio->setPayloadSize(RF_PAYLOAD_SIZE);
		radio->openWritingPipe(RF_WRITE_PIPE); // 00002
		radio->openReadingPipe(1, RF_READ_PIPE); // 00001
		radio->setPALevel(RF24_PA_MIN);
		radio->setDataRate(RF24_250KBPS );
		radio->startListening();

		this->radioStarted = true;
		Serial.println(F("Radio Begin"));
		//printDetails();
	}
	else{
		Serial.println(F("Radio ERROR"));
		this->radioStarted = false;
	}
	resetCCTimer();
}

bool RFTransceiver::isRadioStarted(){
	return this->radioStarted;
}

bool RFTransceiver::isConnected(){
	return this->connected;
}

void RFTransceiver::startConnectivityCheck(){
	this->ccCount = 0;
	resetCCTimer();
}

void RFTransceiver::stopConnectivityCheck(){
	this->ccCount = 4;
}

void RFTransceiver::setActionListener(IActionListener* listener){
	this->actionListener = listener;
}

void RFTransceiver::setAutoSleep(bool autoSleep){
	this->autoSleep = autoSleep;
	timeS = millis();
}

bool RFTransceiver::isAutoSleep(){
	return this->autoSleep;
}

void RFTransceiver::powerDown(){
	if(!active)
		return ;
	this->radio->stopListening();
	this->radio->powerDown();
	this->active = false;
	Serial.println(F("Radio PowerDown"));
}

void RFTransceiver::powerUp(){
	if(active)
			return;
	this->radio->powerUp();
	this->radio->startListening();
	this->active = true;
	timeS = millis();
	Serial.println(F("Radio PowerUp"));
}

bool RFTransceiver::write(const char* msg){
	if(!isRadioStarted())
		return false;
	powerUp();
	Serial.print(F("RF Sent: "));
	Serial.println(msg);

	radio->stopListening();

	bool res = radio->write(msg, RF_PAYLOAD_SIZE);
	/*if(!res){
		Serial.println(F("RF Write Error"));
	}else{
		Serial.println(F("RF Write SUCCED"));
	}*/
	//delay(1);
	onMessageSend(msg);
	radio->startListening();
	timeS = millis();
	return res;
}

void RFTransceiver::printDetails(){
	if(!isRadioStarted()){
		Serial.println(F("Radio ERROR"));
			return;
	}
	radio->printDetails();
}

void RFTransceiver::validate(){
	if(!isRadioStarted())
			return;
	if(radio->available()){
		char msg[RF_PAYLOAD_SIZE];
		radio->read(msg, RF_PAYLOAD_SIZE);
		msg[RF_PAYLOAD_SIZE] = '0';
		onMessageReceived(msg);
		timeS = millis();
	}
	validateConnectivity();
	validateSleep();
}

void RFTransceiver::validateConnectivity(){
	unsigned long interval = millis()-time;
	unsigned int ccIntervals = RF_CC_INTERVALS;
	if(isRadioStarted()){
		//unsigned long subinterval = interval - period;
		if(ccCount==0){
			onSendACK(ccCount);
			resetCCTimer();
			ccCount++;
		}
		else if(ccCount==1 && interval > ccIntervals){
			onSendACK(ccCount);
			resetCCTimer();
			ccCount++;
		}
		else if(ccCount==2 && interval > ccIntervals){
			onSendACK(ccCount);
			resetCCTimer();
			ccCount++;
		}
		else if(ccCount==3 && interval > ccIntervals){
			setConnectionState(false);
			resetCCTimer();
			ccCount++;
		}

		if(ccCount==4 && interval > RF_CC_PERIOD){
			startConnectivityCheck();
		}
	}
}

void RFTransceiver::validateSleep(){
	if(isAutoSleep() && isRadioStarted()){
		unsigned long interval = millis()-timeS;
		if(active && interval > RF_PD_PERIOD){
			powerDown();
		}
		if(!active && interval > RF_PU_PERIOD){
			powerUp();
			this->radio->startListening();
		}
	}
}

void RFTransceiver::resetCCTimer(){
	this->time = millis();
}

void RFTransceiver::setConnectionState(bool state){
	if(connected != state){
		connected = state;
		onConnectionStateChanged(state);
	}
}

void RFTransceiver::onMessageReceived(const char* msg){
	resetCCTimer();
	stopConnectivityCheck();
	setConnectionState(true);

	Action action(this, ON_MESSAGE_RECEIVED, nullptr, msg);
	notifyActionPerformed(action);
}

void RFTransceiver::onMessageSend(const char* msg){
	Action action(this, ON_MESSAGE_SEND, nullptr, msg);
	notifyActionPerformed(action);
}

void RFTransceiver::onConnectionStateChanged(bool state){
	Action action(this, ON_CONNECTION_STATE, nullptr, &state);
	notifyActionPerformed(action);
}

void RFTransceiver::notifyActionPerformed(Action& action){
	if(this->actionListener)
		this->actionListener->actionPerformed(action);
}

void RFTransceiver::onSendACK(uint8_t count){
	char at[RF_PAYLOAD_SIZE];
	char str[] = CMD_ACK;
	sprintf (at, "AT+%s", str);
	write(at);
}

