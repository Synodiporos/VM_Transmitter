/*
 * CMDErrorReport.cpp
 *
 *  Created on: 24 Ιουλ 2018
 *      Author: Synodiporos
 */

#include "../CMD/CMDErrorReport.h"

CMDErrorReport::CMDErrorReport() : CMD(){
	// TODO Auto-generated constructor stub

}

CMDErrorReport::~CMDErrorReport() {
	// TODO Auto-generated destructor stub
}

string CMDErrorReport::getName(){
	return "ER";
}

int CMDErrorReport::execute(){

	return 1;
}
