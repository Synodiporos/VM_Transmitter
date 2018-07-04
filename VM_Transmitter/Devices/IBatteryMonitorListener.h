/*
 * IBatteryMonitorListener.h
 *
 *  Created on: Jul 4, 2018
 *      Author: sgeorgiadis
 */

#ifndef DEVICES_IBATTERYMONITORLISTENER_H_
#define DEVICES_IBATTERYMONITORLISTENER_H_
//#include "BatteryMonitor.h"

class BatteryMonitor;

class IBatteryMonitorListener {
public:
	virtual ~IBatteryMonitorListener(){};

	virtual void onBatteryValueChanged(
			BatteryMonitor* source, short int oldValue) = 0;
	virtual void onBatteryTriggerAlarmStateChanged(
			BatteryMonitor* source, bool alarm) = 0;

};

#endif /* DEVICES_IBATTERYMONITORLISTENER_H_ */
