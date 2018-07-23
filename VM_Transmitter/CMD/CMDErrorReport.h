/*
 * CMDErrorReport.h
 *
 *  Created on: 24 Ιουλ 2018
 *      Author: Synodiporos
 */

#ifndef CMD_CMDERRORREPORT_H_
#define CMD_CMDERRORREPORT_H_
#include "CMD.h"

class CMDErrorReport {
public:
	CMDErrorReport();
	virtual ~CMDErrorReport();
	virtual int execute();
};

#endif /* CMD_CMDERRORREPORT_H_ */
