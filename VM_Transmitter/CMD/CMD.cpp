/*
 * CMD.cpp
 *
 *  Created on: Jul 23, 2018
 *      Author: sgeorgiadis
 */

#include "Arduino.h"
#include "CMD.h"

CMD::CMD(){

}

CMD::CMD(string name) : name(name){
	// TODO Auto-generated constructor stub
}

CMD::CMD(std::vector<string>& params) : params(params){

}

CMD::CMD(std::string name, std::vector<string>& params) :
	name(name), params(params){

}

CMD::~CMD() {
	// TODO Auto-generated destructor stub
}

void CMD::setName(std::string name){
	this->name = name;
}

string CMD::getName(){
	return this->name;
}

void CMD::setParams(vector<string>& params){
	this->params = params;
}

vector<string>& CMD::getParams(){
	return this->params;
}

virtual void CMD::setSource(uint8_t source){

}

virtual uint8_t CMD::getSource(){
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
			Serial.print( ", " );
	}
	Serial.println("]");
}

