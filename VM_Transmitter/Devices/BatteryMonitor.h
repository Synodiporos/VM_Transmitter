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
#include "IBatteryMonitorListener.h"
#include "Arduino.h"
#include <vector>
using namespace std;

//class IBatteryMonitorListener;

class BatteryMonitor : public IActionListener{
public:
	BatteryMonitor(uint8_t pinNumber,
			uint8_t spv,
			unsigned short int measPeriod,
			unsigned short int alarmTriggerValue,
			unsigned short int hysteresis,
			unsigned short int dischargeValue,
			unsigned short int fullchargeValue
			);
	virtual ~BatteryMonitor();
	void initialize();
	void startRecord();
	void pauseRecord();
	void stopRecord();

	AnalogInput* getAnalogInput();
	void setDischargeValue(short int dischargeValue);
	short int getDischargeValue();
	void setFullchargeValue(short int fullchargeValue);
	short int getFullchargeValue();
	void setMeasurementPeriod(short int measPeriod);
	short int getMeasurementPeriod();
	void setAlarmTriggerValue(unsigned short int atv);
	unsigned short int getAlarmTriggerValue();
	void setHysteresis(short int hysteresis);
	short int getHysteresis();


	unsigned short int getValue();
	uint8_t getPercentage();
	float getVoltage(float aref);

	void addBatteryMonitorListener(IBatteryMonitorListener* listener);
	void removeBatteryMonitorListener(IBatteryMonitorListener* listener);
	IBatteryMonitorListener* getBatteryMonitorListener(
			unsigned short int index);
	std::vector<IBatteryMonitorListener*>
		getBatteryMonitorListeners();

	void actionPerformed(Action action);
	void validate();

protected:
	Timer timer ;
	unsigned short int measPeriod ;
	unsigned short int dischargeValue;
	unsigned short int fullchargeValue;
	unsigned short int alarmTriggerValue;
	short int hysteresis;
	AnalogInput analog;
	unsigned short int oldMeas = -1;
	bool alarm = false;

	std::vector<IBatteryMonitorListener*>
		batteryListeners = std::vector<IBatteryMonitorListener*>();

	void onValueChanged(unsigned short int oldValue);
	void onAlarmStateChanged();
	void notifyBatteryValueChanged(short int oldValue);
	void notifyBatteryTriggerAlarmStateChanged();

};

#endif /* DEVICES_BATTERYMONITOR_H_ */
