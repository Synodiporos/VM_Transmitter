/*
 * CMDTestLeds.cpp
 *
 *  Created on: 28 Ιουλ 2018
 *      Author: Synodiporos
 */

#include "CMDTestLeds.h"

CMDTestLeds::CMDTestLeds() {
	// TODO Auto-generated constructor stub

}

CMDTestLeds::~CMDTestLeds() {
	// TODO Auto-generated destructor stub
}

string CMDTestLeds::getName(){
	return "TLS";
}

uint8_t CMDTestLeds::onExecute(){
	string param = getParams()[0];
	if(param.compare("w")){

	}
	else if(param.compare("r")){

	}
	else if(param.compare("g")){

	}
	else if(param.compare("a")){

	}
	else{
		return RES_WRONGPARAMS;
	}
	return RES_ONPROGRESS;
}

void CMDTestLeds::validate(){
	CMD::validate();
}
