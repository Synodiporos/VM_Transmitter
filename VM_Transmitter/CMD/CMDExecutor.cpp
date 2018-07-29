/*
 * CMDExecutor.cpp
 *
 *  Created on: Jul 23, 2018
 *      Author: sgeorgiadis
 */

#include "../CMD/CMDExecutor.h"

CMDExecutor::CMDExecutor() {
	// TODO Auto-generated constructor stub

}

CMDExecutor::~CMDExecutor() {
	// TODO Auto-generated destructor stub
}

void CMDExecutor::begin(){

}

bool CMDExecutor::pushCMD(CMD* cmd){
	if(cmd){
		this->vector.push_back(cmd);
		cmd->setStateListener(this);
		return true;
	}
	return false;
}

bool CMDExecutor::removeCMD(CMD* cmd){
	std::vector<CMD*>::iterator it;
	it = find(vector.begin(), vector.end(), cmd);
	if(cmd){
		vector.erase(it);
		return true;
	}
	return false;
}

bool CMDExecutor::isEmpty(){
	return this->vector.empty();
}

void CMDExecutor::clear(){
   std::vector<CMD*> empty;
   std::swap(vector, empty );
}

void CMDExecutor::stateChanged(State* state){
	if(state){
		CMD* source = (CMD*)state->getSource();
		uint8_t st = source->getState();
		if(st == STATE_COMPLETED){
			this->removeCMD(source);
		}
	}
}

void CMDExecutor::validate(){
	for(std::vector<CMD*>::iterator it = vector.begin();
				it != vector.end(); ++it) {
		CMD* cmd = *it;
		if(cmd && cmd->isExecuted())
			cmd->validate();
	}
}
