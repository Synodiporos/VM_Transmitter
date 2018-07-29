/*
 * CMDExecutor.h
 *
 *  Created on: Jul 23, 2018
 *      Author: sgeorgiadis
 */

#ifndef CMD_CMDEXECUTOR_H_
#define CMD_CMDEXECUTOR_H_

#include <vector>
using namespace std;
#include "../CMD/CMD.h"
#include "../Commons/IStateListener.h"

class CMDExecutor : public IStateListener{
public:
	CMDExecutor();
	virtual ~CMDExecutor();

	bool pushCMD(CMD* cmd);
	bool removeCMD(CMD* cmd);
	bool isEmpty();
	void clear();
	void stateChanged(State* state);
	void validate();


private:
	vector<CMD*> vector;

	void begin();
};

#endif /* CMD_CMDEXECUTOR_H_ */
