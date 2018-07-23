/*
 * ATCommands.h
 *
 *  Created on: Jul 23, 2018
 *      Author: sgeorgiadis
 */

#ifndef AT_ATCOMMANDS_H_
#define AT_ATCOMMANDS_H_
#include <string>
using namespace std;

class ATCommands {
public:

	static const string AT_BT = "BT";
	static const string AT_HV = "HV";
	static const string AT_SETS = "SETS";
	static const string AT_SET = "SET";
	static const string AT_TLS = "TLS"; //Test LEDs
	static const string AT_TBZ = "TBZ"; //Test Buzzer

};

#endif /* AT_ATCOMMANDS_H_ */
