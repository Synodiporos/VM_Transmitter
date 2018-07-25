/*
 * CMD.cpp
 *
 *  Created on: Jul 23, 2018
 *      Author: sgeorgiadis
 */

#include "../CMD/CMD.h"
using namespace std;
#include "Arduino.h"

CMD::CMD(){

}

CMD::CMD(std::vector<string>& params) : params(params){

}

CMD::~CMD() {
	// TODO Auto-generated destructor stub
}

string CMD::getName(){
	return "Unknown CMD";
}

void CMD::setParams(vector<string>& params){
	this->params = params;
}

vector<string>& CMD::getParams(){
	return this->params;
}

void CMD::setSource(uint8_t source){
	this->source = source;
}

uint8_t CMD::getSource(){
	return this->source;
}

void CMD::print(){
	Serial.print("CMD ");
	Serial.print(getName().c_str());
	Serial.print("[");
	vector<string> p = getParams();

	for(std::vector<string>::iterator it = p.begin();
				it != p.end(); ++it) {
		Serial.print( ((string)*it).c_str() );
		if(it!=p.end()-1)
			Serial.print( ", ");
	}
	Serial.println( "]" );
}

