/*
 * BatteryMonitor.h
 *
 *  Created on: Jul 3, 2018
 *      Author: sgeorgiadis
 */

#ifndef DEVICES_BATTERYMONITOR_H_
#define DEVICES_BATTERYMONITOR_H_
#include "../Commons/IStateListener.h"
#include "../Commons/IActionListener.h"
#include "../Commons/Action.h"
#include "../System/SystemConstants.h"
#include "../Timer/Timer.h"
#include "../Math/MathUtil.h"
#include "IBatteryMonitorListener.h"
#include "../AnalogInput/Filters/FilterOnePole.h"
#include "Arduino.h"
#include <vector>
using namespace std;

//class IBatteryMonitorListener;

class BatteryMonitor{
public:
	virtual ~BatteryMonitor();
	static BatteryMonitor* getInstance();
	void initialize();
	void measure();
	//void startRecord();
	//void pauseRecord();
	//void stopRecord();
	bool isAlarmEnabled();

	float getMeasurementValue();
	uint8_t getPercentage();
	float getVoltage(float aref);

	void setBatteryMonitorListener(IBatteryMonitorListener* listener);
	IBatteryMonitorListener* getBatteryMonitorListener();

	void validate();

protected:
	static BatteryMonitor* instance;
	uint8_t state = 0;
	unsigned long time = 0;
	unsigned int measurement = 0;
	FilterOnePole filter = FilterOnePole(LOWPASS, BATTM_FREQ, 1023);
	bool alarm = false;
	IBatteryMonitorListener* listener = nullptr;

	BatteryMonitor();
	void setMeasurement(unsigned int meas);
	void onValueChanged(unsigned short int oldValue);
	void onAlarmStateChanged();
	void notifyBatteryValueChanged(short int oldValue);
	void notifyBatteryTriggerAlarmStateChanged();
	int toIntValue(unsigned int value);
};

#endif /* DEVICES_BATTERYMONITOR_H_ */
