/*
 * Controller.h
 *
 *  Created on: Jul 4, 2018
 *      Author: sgeorgiadis
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_
#include "Commons/IActionListener.h"
#include "Commons/Action.h"
#include "Commons/IPropertyListener.h"
#include "Commons/IStateListener.h"
#include "Devices/HVProbe.h"
#include "Devices/BatteryMonitor.h"
#include "Devices/IBatteryMonitorListener.h"
#include "Devices/HVProbe.h"
#include "System/SystemConstants.h"
#include "System/NotificationSystem.h"

class Controller : public IBatteryMonitorListener,
	IPropertyListener{
public:
	Controller();
	virtual ~Controller();

	void activate();
	void deactivate();

	void setBatteryMonitor(BatteryMonitor* batteryMonitor);
	void setHVProbe(HVProbe* hvProbe);
	void setNotificationSystem(NotificationSystem* ns);
	void setLoggerSystem();
	void setRFDevice();

	void propertyChanged(
				void* source,
				unsigned short int propertyId,
				const void* oldPropery);

	void onHVProbeVoltageChanged(unsigned short int value);
	void onBatteryValueChanged(
				BatteryMonitor* source, short int value);
	void onBatteryTriggerAlarmStateChanged(
				BatteryMonitor* source, bool alarm);

protected:
	BatteryMonitor* batteryMonitor = nullptr;
	HVProbe* hvProbe = nullptr;
	NotificationSystem* notification = nullptr;
};

#endif /* CONTROLLER_H_ */
