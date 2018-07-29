/*
 * SerialBroadcaster.cpp
 *
 *  Created on: 21 Ιουλ 2018
 *      Author: Synodiporos
 */
#include "Arduino.h"
#include "SerialBroadcaster.h"
#include "../Memory/MemoryFree.h"
#include "../Memory/pgmStrToRAM.h"

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
		//inputString += inChar;
		// if the incoming character is a newline, set a flag so the main loop can
		// do something about it:
		if (inChar == '\n' || inChar == '\r') {
			//inputString.erase(std::remove_if(
			//		inputString.begin(), inputString.end(), std::isspace),
			//		inputString.end());
			if(inputString.size()>0){
				inputString.push_back('\r');
				onSerialMessageReceived(inputString);
			}
		}
		else
			inputString.push_back(inChar);
	}
	delay(10);
}

void SerialBroadcaster::onSerialMessageReceived(const string& msg){
	Serial.print(F("Received: "));
	const char* c = msg.c_str();
	Serial.println(c);
	//msg += "\r";

	CMD* cmd = new CMDErrorReport();//AT::toCMD(msg);
	//cmd->print();
	//cmd->execute();

	//delete cmd;
	inputString.clear();

	Serial.print(F("Free RAM = "));
	Serial.println(freeMemory(), DEC);
	delete cmd;
	delete c;
}
