/*
 * SurgeMonitor.h
 *
 *  Created on: 4 Σεπ 2018
 *      Author: Synodiporos
 */

#ifndef DEVICES_SURGEMONITOR_H_
#define DEVICES_SURGEMONITOR_H_

#include <Arduino.h>
#include "../System/SystemConstants.h"
#include "../Commons/IActionListener.h"
#include "../Commons/Action.h"
#include <stdint.h>

#define NOM 5

class SurgeMonitor {
public:
	static const unsigned short int ON_SURGE_APPLIED = 20;

	SurgeMonitor();
	virtual ~SurgeMonitor();
	void setActionListener(IActionListener* listener);
	IActionListener* getActionListener();
	void setDevice(uint8_t device);
	uint8_t getDevice();
	bool isCharging();
	void setMeasurement(unsigned int measurement);
	void validate();


private:
	uint8_t device = 0;
	unsigned int initMeasure = 0;
	unsigned int maxMeasure = 0;
	unsigned int buf[NOM];
	uint8_t state = 0;
	uint8_t i = 0;
	unsigned long time = 0;
	IActionListener* actionListener = nullptr;

	void setMaxMeasurement(unsigned int max);
	void clearBuffer();
	void onCharging();
	void onDischarged();
	void notifyActionListener(unsigned int data[3]);
};

#endif /* DEVICES_SURGEMONITOR_H_ */
