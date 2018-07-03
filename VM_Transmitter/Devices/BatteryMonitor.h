/*
 * BatteryMonitor.h
 *
 *  Created on: Jul 3, 2018
 *      Author: sgeorgiadis
 */

#ifndef DEVICES_BATTERYMONITOR_H_
#define DEVICES_BATTERYMONITOR_H_
#include "../AnalogInput/AnalogInput.h"
#include "../Commons/IPropertyListener.h"
#include "../Commons/IActionListener.h"
#include "../Commons/Action.h"
#include "../System/SystemConstants.h"
#include "../Timer/Timer.h"
#include "../Math/MathUtil.h"
#include "Arduino.h"


class BatteryMonitor : IPropertyListener, IActionListener{
public:
	BatteryMonitor();
	virtual ~BatteryMonitor();
	void initialize();

	uint8_t getPercentage();
	float getVoltage();

	void propertyChanged(
				void* source,
				unsigned short int propertyId,
				const void* oldPropery);
	void actionPerformed(Action action);
	void validate();

protected:
	AnalogInput analog = AnalogInput(BT_ANALOG_PIN, BATTM_SPV);
	Timer timer = Timer(32, 32, 3);
	unsigned short int oldValue = 0;

};

#endif /* DEVICES_BATTERYMONITOR_H_ */
