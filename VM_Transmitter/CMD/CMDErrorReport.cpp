/*
 * CMDErrorReport.cpp
 *
 *  Created on: 24 Ιουλ 2018
 *      Author: Synodiporos
 */

#include "../CMD/CMDErrorReport.h"
#include "Arduino.h"
CMDErrorReport::CMDErrorReport() : CMDErrorReport('0'){
}

CMDErrorReport::CMDErrorReport(char code) : CMD() {
	setErrorCode(code);
}

CMDErrorReport::~CMDErrorReport() {
	// TODO Auto-generated destructor stub
}

void CMDErrorReport::setErrorCode(char code){
	string c;
	c.push_back(code);
	getParams().push_back(c);
}

string CMDErrorReport::getName(){
	return "ER";
}

uint8_t CMDErrorReport::onExecute(){
	return RES_COMPLETED;
}

void CMDErrorReport::validate(){
	CMD::validate();
}

