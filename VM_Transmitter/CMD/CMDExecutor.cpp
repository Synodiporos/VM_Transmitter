/*
 * CMDExecutor.cpp
 *
 *  Created on: Jul 23, 2018
 *      Author: sgeorgiadis
 */

#include "../CMD/CMDExecutor.h"

CMDExecutor* CMDExecutor::instance = nullptr;

CMDExecutor::CMDExecutor() {
	// TODO Auto-generated constructor stub

}

CMDExecutor::~CMDExecutor() {
	// TODO Auto-generated destructor stub
}


CMDExecutor* CMDExecutor::getInstance(){
	if(CMDExecutor::instance == nullptr){
		instance = new CMDExecutor();
	}
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
	std::vector<CMD*>::iterator iter;
	//it = std::find(vector.begin(), vector.end(), cmd);
	for(std::vector<CMD*>::iterator it = vector.begin();
					it != vector.end(); ++it) {
		if(*it==cmd)		{
			iter = it;
			break;
		}
	}
	if(cmd){
		vector.erase(iter);
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


void CMDExecutor::validate(){
	for(std::vector<CMD*>::iterator it = vector.begin();
				it != vector.end(); ++it) {
		CMD* cmd = *it;
		//if(cmd && cmd->isExecuted())
			cmd->validate();
	}
}
