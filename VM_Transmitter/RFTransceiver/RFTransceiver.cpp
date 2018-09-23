/*
 * RFTransceiver.cpp
 *
 *  Created on: Jul 6, 2018
 *      Author: sgeorgiadis
 */

#include "RFTransceiver.h"
#include <SPI.h>
#include <RF24.h>

RFTransceiver* RFTransceiver::instance = nullptr;

RFTransceiver::~RFTransceiver() {
	// TODO Auto-generated destructor stub
}

RFTransceiver::RFTransceiver(RF24 &radio) : radio(radio) {
	// TODO Auto-generated constructor stub
	//initialize();
}

RFTransceiver* RFTransceiver::getInstance(RF24 &radio){
	if(instance==nullptr){
		instance = new RFTransceiver(radio);
	}
	return instance;
}

bool RFTransceiver::setEnabled(bool enabled){
	if(this->enabled!=enabled){
		this->enabled = enabled;
		return true;
	}
	return false;
}

bool RFTransceiver::isEnabled(){
	return this->enabled;
}

uint8_t RFTransceiver::getState(){
	return this->state;
}

//SLAVE
void RFTransceiver::initialize() {
//	this->radio = radio;
	if(radio.begin()){
		radio.setRetries(10, 3);
		radio.disableDynamicPayloads();
		radio.setPayloadSize(RF_PAYLOAD_SIZE);
		radio.openWritingPipe(RF_WRITE_PIPE); // 00002
		radio.openReadingPipe(1, RF_READ_PIPE); // 00001
		radio.setPALevel(RF_PALEVEL);
		radio.setDataRate(RF_DATARATE);
		//radio.startListening();
		setState(RF_STATE_INITIALIZED);
	}
	else{
		setState(RF_STATE_INITIALIZE_ERROR);
	}
}

bool RFTransceiver::isActivated(){
	return this->active;
}

bool RFTransceiver::isInitialized(){
	return getState() >= RF_STATE_INITIALIZED;
}

bool RFTransceiver::isConnecting(){
	uint8_t state = getState();
	return state>=RF_STATE_CONNECTING &&
			state<=(RF_STATE_CONNECTING + RF_RETRIES);
}

bool RFTransceiver::isConnected(){
	return getState() >= RF_STATE_CONNECTED;
}

/*void RFTransceiver::startConnectivityCheck(){
	uint8_t state = getState();
	if(state==RF_STATE_CONNECTED ||
			(state==RF_STATE_INITIALIZED ||
					state==RF_STATE_DISCONNECTED)){
		setState(RF_STATE_CONNECTING);
		helper = 2;
		time = millis();
	}
}

void RFTransceiver::stopConnectivityCheck(){
	if(isConnecting()){
		setState(RF_STATE_DISCONNECTED);
	}
}*/

void RFTransceiver::setActionListener(IActionListener* listener){
	this->actionListener = listener;
}

bool RFTransceiver::powerUp(){
	if(!isEnabled() || !isInitialized()
			|| isActivated())
		return false;

	radio.powerUp();
	this->active = true;
	Serial.println(F("Radio PowerUp"));
	return true;
}


bool RFTransceiver::powerDown(){
	if(!isEnabled() || !isInitialized()
			|| !isActivated())
		return false;

	stopListening();
	delay(4);
	radio.powerDown();
	this->active = false;
	Serial.println(F("Radio PowerDown"));
	return true;
}

bool RFTransceiver::startListening(){
	if(isInitialized() && !isListening()){
		radio.startListening();
		listen = true;
		return true;
	}
	return false;
}

bool RFTransceiver::stopListening(){
	if(isInitialized() && isListening()){
		radio.stopListening();
		listen = false;
		return true;
	}
	return false;
}

bool RFTransceiver::isListening(){
	return this->listen;
}

bool RFTransceiver::write(const char* msg){
	if(!isEnabled() || !isActivated() ||
			!isInitialized())
		return false;
	//powerUp();
	//Serial.print(F("RF Sent: "));
	//Serial.println(msg);

	stopListening();
	//delay(2);

	bool res = radio.write(msg, strlen(msg));
	if(!res){
		onMessageSendError(msg);
	}else{
		onMessageSend(msg);
	}

	//delay(2);
	startListening();

	return res;
}

bool RFTransceiver::send(const char* msg, uint8_t ackId){
	if(!isEnabled())
		return false;
	if(!isInitialized())
		return false;

	CharUtil::copyCharArray(msg, request, 24);
	this->requestId = ackId;
	Serial.println(request);
	setState(RF_STATE_CONNECTING);
	return true;
}

void RFTransceiver::printDetails(){
	if(!isInitialized()){
		return;
	}
	radio.printDetails();
}

void RFTransceiver::validate(){
	if(!isEnabled())
		return;
	if(!isInitialized())
		return;

	if(radio.available()){
		char msg[RF_PAYLOAD_SIZE];
		radio.read(msg, RF_PAYLOAD_SIZE);
		msg[RF_PAYLOAD_SIZE] = '0';
		onMessageReceived(msg);
	}

	if(isConnecting()){
		if(helper==1){
			if(millis()-time > RF_CONNECTION_CHECK_INTERVALS){
				if(state >= RF_STATE_CONNECTING + RF_RETRIES)
					setState(RF_STATE_DISCONNECTED);
				else{
					helper = 2;
				}
			}
		}else if(helper==2){
			helper = 1;
			time = millis();
			setState(++state);
		}
	}
}

bool RFTransceiver::setActiveState(bool active){
	if(this->active!=active){
		this->active = active;
		return true;
	}
	return false;
}

void RFTransceiver::onActiveStateChanged(){
	Action action(this, ON_ACTIVE_STATE, nullptr, &active);
	notifyActionPerformed(action);
}

bool RFTransceiver::setState(uint8_t state){
	if(this->state != state){
		this->state = state;
		onStateChanged();
		return true;
	}
	return false;
}

void RFTransceiver::onStateChanged(){
	Action action(this, ON_CONNECTION_STATE, nullptr, &state);
	notifyActionPerformed(action);

	if(state==RF_STATE_CONNECTED){
		helper = 0;
		time = millis();
	}
	else if(state >= RF_STATE_CONNECTING &&
			state < RF_STATE_CONNECTING + RF_RETRIES){
		onSendRequest();
		helper = 0;
		time = millis();
	}
	else if(state == RF_STATE_DISCONNECTED){
		helper = 0;
		time = millis();
	}
	else {

	}
}

void RFTransceiver::onMessageSend(const char* msg){
	Action action(this, ON_MESSAGE_SEND, nullptr, msg);
	notifyActionPerformed(action);
}

void RFTransceiver::onMessageSendError(const char* msg){
	Action action(this, ON_MESSAGE_SEND_ERROR, nullptr, msg);
	notifyActionPerformed(action);
}

void RFTransceiver::onMessageReceived(const char* msg){
	Action action(this, ON_MESSAGE_RECEIVED, nullptr, msg);
	notifyActionPerformed(action);
	//stopConnectivityCheck();

	if(isInitialized()){
		String cmd;
		uint8_t id;
		char params[3][8] = {'\0','\0','0'};
		uint8_t res = CharUtil::parse(msg, cmd, id, params);
		if(res){
			setState(RF_STATE_CONNECTED);
			if(cmd.compareTo(CMD_ACR)){
				onResponseReceived(msg, id);
				if(id>0 && requestId==id){
					request[0] = 0;
					requestId = 0;
				}
			}
		}
	}
}

void RFTransceiver::onResponseReceived(const char* msg, uint8_t id){
	Action action(this, ON_RESPONSE_RECEIVED, nullptr, msg);
	notifyActionPerformed(action);
}

void RFTransceiver::notifyActionPerformed(Action& action){
	if(this->actionListener)
		this->actionListener->actionPerformed(action);
}

void RFTransceiver::onSendRequest(){
	if(strlen(request)>0)
		write(request);
}

