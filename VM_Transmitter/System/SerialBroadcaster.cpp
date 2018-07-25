/*
 * SerialBroadcaster.cpp
 *
 *  Created on: 21 Ιουλ 2018
 *      Author: Synodiporos
 */
#include "Arduino.h"
#include "SerialBroadcaster.h"

SerialBroadcaster* SerialBroadcaster::instance = 0;

SerialBroadcaster::SerialBroadcaster() {
	// TODO Auto-generated constructor stub

}

SerialBroadcaster::~SerialBroadcaster() {
	// TODO Auto-generated destructor stub
}

SerialBroadcaster* SerialBroadcaster::getInstance(){
	if(!instance){
		instance = new SerialBroadcaster();
	}
	return instance;
}

void SerialBroadcaster::validate(){
	int ss = Serial.available();
	if (ss>0) {
		// get the new byte:
		char inChar = (char)Serial.read();
		// add it to the inputString:
		inputString += inChar;
		// if the incoming character is a newline, set a flag so the main loop can
		// do something about it:
		if (inChar == '\n') {
		  onSerialMessageReceived(inputString);
		}
	}
	delay(1);
}

void SerialBroadcaster::onSerialMessageReceived(const string& msg){
	Serial.print("Received: ");
	Serial.println(msg.c_str());

	//msg += "\r";

	CMD* cmd = AT::toCMD(msg);
	cmd->print();

	delete cmd;
	inputString = "";
}
