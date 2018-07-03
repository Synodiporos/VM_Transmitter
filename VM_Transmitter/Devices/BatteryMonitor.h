/*
 * BatteryMonitor.h
 *
 *  Created on: Jul 3, 2018
 *      Author: sgeorgiadis
 */

#ifndef DEVICES_BATTERYMONITOR_H_
#define DEVICES_BATTERYMONITOR_H_
#include "../AnalogInput/ToggleAnalogInput.h"
#include "../Commons/IStateListener.h"
#include "../Commons/IActionListener.h"
#include "../Commons/Action.h"
#include "../System/SystemConstants.h"
#include "../Timer/Timer.h"
#include "../Math/MathUtil.h"
#include "Arduino.h"

class BatteryMonitor : IStateListener, IActionListener{
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
	void stateChanged(State* state);
	void validate();

protected:
	ToggleAnalogInput analog =
			ToggleAnalogInput(BT_ANALOG_PIN, BATTM_SPV,
					BATTM_DISC_VOLTAGE, BATTM_HYSTERISIS_VALUE);
	Timer timer = Timer(64, BATTM_SPV, 3);

	short int dischargeValue = 0;
	short int fullchargeValue = 1023;
	short int alarmTriggerValue = 512;
	//float referenceVoltage = 5.0;
	short int measPeriod = 1024;

	unsigned short int oldValue = 0;

};

#endif /* DEVICES_BATTERYMONITOR_H_ */
