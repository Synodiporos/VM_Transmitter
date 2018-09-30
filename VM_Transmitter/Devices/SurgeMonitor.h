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
#include "../System/UnixTime.h"
#include "../Commons/IActionListener.h"
#include "../Commons/Action.h"
#include <stdint.h>

#define NOM 5
#define NOR 13
#define SM_CHARGE_INTERVAL 320
#define SM_STATE_CHARGING 2
#define SM_STATE_CHARGED 1
#define SM_STATE_DISCHARGED 0

struct Surge{
	uint32_t datetime;
	uint8_t device;
	uint32_t charge;
	uint16_t slope;
};

class SurgeMonitor {
public:
	static const unsigned short int ON_SM_STATE_CHANGED = 20;

	SurgeMonitor();
	virtual ~SurgeMonitor();
	uint8_t getState();
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
	uint8_t count = 0;
	unsigned long time = 0;
	unsigned long timeCharge = 0;
	IActionListener* actionListener = nullptr;

	void setState(uint8_t state);
	void setMaxMeasurement(unsigned int max);
	void clearBuffer();
	void onCharging();
	void onCharged();
	void onDischarged();
	void notifyActionListener();
};

#endif /* DEVICES_SURGEMONITOR_H_ */
