/*
 * RFTransceiver.h
 *
 *  Created on: Jul 6, 2018
 *      Author: sgeorgiadis
 */

#ifndef RFTRANSCEIVER_RFTRANSCEIVER_H_
#define RFTRANSCEIVER_RFTRANSCEIVER_H_
#include "../Commons/IActionListener.h"
#include "../Commons/Action.h";
#include "../Timer/Timer.h"


class RFTransceiver : IActionListener{
public:
	static const unsigned short int ON_CONNECTION_CHECK = 90;
	virtual ~RFTransceiver();

	static RFTransceiver* getInstance();

	void initialize();
	void setCheckForConnectivity(bool enabled);
	bool isCheckForConnectinty();

	void actionPerformed(Action action);

private:
	RFTransceiver();
	static RFTransceiver* instance;

	Timer timer = Timer(1000, 0, ON_CONNECTION_CHECK);

};

#endif /* RFTRANSCEIVER_RFTRANSCEIVER_H_ */
