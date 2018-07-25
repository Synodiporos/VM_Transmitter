/*
 * CMDErrorReport.h
 *
 *  Created on: 24 Ιουλ 2018
 *      Author: Synodiporos
 */

#ifndef CMD_CMDERRORREPORT_H_
#define CMD_CMDERRORREPORT_H_
#include "../CMD/CMD.h"

class CMDErrorReport : public CMD{
public:
	CMDErrorReport();
	virtual ~CMDErrorReport();
	string getName();
	int execute();
};

#endif /* CMD_CMDERRORREPORT_H_ */
