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
		this->queue.push(cmd);
		return true;
	}
	return false;
}

bool CMDExecutor::isEmpty(){
	return this->queue.empty();
}

void CMDExecutor::clear()
{
   std::queue<CMD*> empty;
   std::swap(queue, empty );
}
