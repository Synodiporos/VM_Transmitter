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
	while (Serial.available()) {
		// get the new byte:
		char inChar = (char)Serial.read();
		// add it to the inputString:
		inputString += inChar;
		// if the incoming character is a newline, set a flag so the main loop can
		// do something about it:
		if (inChar == '\n') {
		  stringComplete = true;
		  onSerialMessageReceived();
		}
	}
}

void SerialBroadcaster::onSerialMessageReceived(){
	Serial.print(inputString.c_str());
	inputString = "";
}
