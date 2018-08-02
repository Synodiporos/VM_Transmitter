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

class BatteryMonitor{
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
	void clearRecordsTable();
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
	bool isAlarmEnabled();


	unsigned short int getMeasurementValue();
	uint8_t getPercentage();
	float getVoltage(float aref);

	void addBatteryMonitorListener(IBatteryMonitorListener* listener);
	void removeBatteryMonitorListener(IBatteryMonitorListener* listener);
	IBatteryMonitorListener* getBatteryMonitorListener(
			unsigned short int index);
	std::vector<IBatteryMonitorListener*>
		getBatteryMonitorListeners();

	void validate();

protected:
	uint8_t analogPin;
	uint8_t spv = 1;
	unsigned short int measPeriod ;
	unsigned short int dischargeValue;
	unsigned short int fullchargeValue;
	unsigned short int alarmTriggerValue;
	short int hysteresis;
	uint8_t state = 0;
	unsigned long time = 0;
	bool alarm = false;
	unsigned short int measurement = 0;
	int total = 0;
	unsigned short int readings[BATTM_SPV];
	unsigned short int readIndex = 0;
	char flag = 0;

	std::vector<IBatteryMonitorListener*>
		batteryListeners = std::vector<IBatteryMonitorListener*>();

	void onValueChanged(unsigned short int oldValue);
	void onAlarmStateChanged();
	void notifyBatteryValueChanged(short int oldValue);
	void notifyBatteryTriggerAlarmStateChanged();

};

#endif /* DEVICES_BATTERYMONITOR_H_ */
