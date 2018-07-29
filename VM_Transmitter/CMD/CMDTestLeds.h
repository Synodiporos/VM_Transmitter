/*
 * CMDTestLeds.h
 *
 *  Created on: 28 Ιουλ 2018
 *      Author: Synodiporos
 */

#ifndef CMD_CMDTESTLEDS_H_
#define CMD_CMDTESTLEDS_H_
#include <string>
using namespace std;
#include "CMD.h"

class CMDTestLeds: public CMD {
public:
	CMDTestLeds();
	virtual ~CMDTestLeds();
	virtual string getName();
	virtual uint8_t onExecute();
	void validate();

private:

};

#endif /* CMD_CMDTESTLEDS_H_ */
