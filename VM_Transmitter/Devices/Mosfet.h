/*
 * Mosfet.h
 *
 *  Created on: Aug 3, 2018
 *      Author: sgeorgiadis
 */

#ifndef DEVICES_MOSFET_H_
#define DEVICES_MOSFET_H_

#include <Arduino.h>
#include "../System/SystemConstants.h"

#define MOS_STATE_ON 1
#define MOS_STATE_OFF 0
#define MOS_STATE_UN 2

class Mosfet {
public:
	virtual ~Mosfet();
	static Mosfet* getInstance();
	bool setState(uint8_t state);
	uint8_t getState();
	bool switchON();
	bool switchOFF();

private:
	Mosfet();
	static Mosfet* instance;
	uint8_t state = 2;

	void onStateChanged();
};

#endif /* DEVICES_MOSFET_H_ */
