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
#include <stdint.h>

#define NOM 5

class SurgeMonitor {
public:
	SurgeMonitor();
	virtual ~SurgeMonitor();
	void setDevice(uint8_t device);
	uint8_t getDevice();
	bool isCharging();
	void setMeasurement(unsigned int measurement);
	void validate();


private:
	uint8_t device = 0;
	unsigned short int maxMeasure = 0;
	unsigned short int buf[NOM];
	uint8_t state = 0;
	uint8_t i = 0;
	unsigned long time = 0;
	void setMaxMeasurement(unsigned int max);
	void clearBuffer();
	void onCharging();
	void onDischarged();
};

#endif /* DEVICES_SURGEMONITOR_H_ */
