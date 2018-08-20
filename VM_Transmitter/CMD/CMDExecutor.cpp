/*
 * CMDExecutor.cpp
 *
 *  Created on: Jul 23, 2018
 *      Author: sgeorgiadis
 */

#include "../CMD/CMDExecutor.h"
#include "Arduino.h"
#include <vector>

CMDExecutor* CMDExecutor::instance = nullptr;

CMDExecutor::CMDExecutor() {
	// TODO Auto-generated constructor stub

}

CMDExecutor::~CMDExecutor() {
	// TODO Auto-generated destructor stub
	delete instance;
}


CMDExecutor* CMDExecutor::getInstance(){
	if(!instance)
		instance = new CMDExecutor();

	return instance;
}

void CMDExecutor::begin(){

}

bool CMDExecutor::pushCMD(CMD* cmd){
	if(cmd){
		this->vector.push_back(cmd);
		return true;
	}
	return false;
}

bool CMDExecutor::removeCMD(CMD* cmd){
	if(!cmd)
		return false;
	//Serial.print(F("removeCmd: "));
	//Serial.println((long)cmd);

	vector.erase(
			remove(vector.begin(), vector.end(), cmd),
			vector.end());

	delete cmd;
	return true;
	/*
	std::vector<CMD*>::iterator* tormv = nullptr;
	for(std::vector<CMD*>::iterator it = vector.begin();
					it != vector.end(); ++it) {
		if(*it==cmd)		{
			tormv = &it;
			break;
		}
	}
	Serial.println((long)tormv);
	if(tormv){
		vector.erase(*tormv);
		return true;
	}
	return false;*/
}

bool CMDExecutor::isEmpty(){
	return this->vector.empty();
}

void CMDExecutor::clear(){
   std::vector<CMD*> empty;
   std::swap(vector, empty );
}


void CMDExecutor::validate(){
	for(CMD* cmd : vector) {
		//if(cmd && cmd->isExecuted())
			cmd->validate();
	}
}
