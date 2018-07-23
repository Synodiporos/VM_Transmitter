/*
 * CMDBatteryReport.cpp
 *
 *  Created on: 23 Ιουλ 2018
 *      Author: Synodiporos
 */

#include "CMDBatteryReport.h"

CMDBatteryReport::CMDBatteryReport() {
	// TODO Auto-generated constructor stub

}

CMDBatteryReport::CMDBatteryReport(std::vector<string>& params) :
	CMD(params){

}

CMDBatteryReport::~CMDBatteryReport() {
	// TODO Auto-generated destructor stub
}

int CMDBatteryReport::execute(){

	return 1;
}
