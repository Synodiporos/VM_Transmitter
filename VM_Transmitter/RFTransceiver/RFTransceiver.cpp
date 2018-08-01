/*
 * RFTransceiver.cpp
 *
 *  Created on: Jul 6, 2018
 *      Author: sgeorgiadis
 */

#include "RFTransceiver.h"

RFTransceiver* RFTransceiver::instance = nullptr;

RFTransceiver::~RFTransceiver() {
	// TODO Auto-generated destructor stub
}

RFTransceiver::RFTransceiver() {
	// TODO Auto-generated constructor stub

}

RFTransceiver* RFTransceiver::getInstance(){
	if(instance==nullptr){
		instance = new RFTransceiver();
	}
	return instance;
}

void RFTransceiver::initialize(){

}
