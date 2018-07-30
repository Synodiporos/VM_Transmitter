/*
 * CMDStartUp.h
 *
 *  Created on: 30 Ιουλ 2018
 *      Author: Synodiporos
 */

#ifndef CMD_CMDSTARTUP_H_
#define CMD_CMDSTARTUP_H_

#include "Arduino.h"
#include "../System/SystemConstants.h"
#include "CMD.h"
#include "../Timer/Timer.h"

class CMDStartUp: public CMD {
public:
	CMDStartUp();
	virtual ~CMDStartUp();
	uint8_t onExecute();
	void validate();

private:
	Timer timer =  Timer(1000, 1);
};

#endif /* CMD_CMDSTARTUP_H_ */
