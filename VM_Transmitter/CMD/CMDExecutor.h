/*
 * CMDExecutor.h
 *
 *  Created on: Jul 23, 2018
 *      Author: sgeorgiadis
 */

#ifndef CMD_CMDEXECUTOR_H_
#define CMD_CMDEXECUTOR_H_

#include <queue>

#include "../CMD/CMD.h"
using namespace std;

class CMDExecutor {
public:
	CMDExecutor();
	virtual ~CMDExecutor();

	bool pushCMD(CMD* cmd);
	bool isEmpty();
	void clear();

	void validate();

private:
	queue<CMD*> queue;

	void begin();
};

#endif /* CMD_CMDEXECUTOR_H_ */
