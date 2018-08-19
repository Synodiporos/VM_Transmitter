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
#include "Commons/IActionListener.h"
#include "Commons/Action.h"
#include "Devices/HVProbe.h"
#include "Devices/BatteryMonitor.h"
#include "Devices/IBatteryMonitorListener.h"
#include "Devices/HVProbe.h"
#include "AnalogInput/Probe.h"
#include "System/SystemConstants.h"
#include "System/NotificationSystem.h"
#include "RFTransceiver/RFTransceiver.h"
#include "CMD/AT.h"
#include <string>

class Controller : public IBatteryMonitorListener,
	IPropertyListener, IActionListener{
public:
	Controller();
	virtual ~Controller();

	void activate();
	void deactivate();
	void initialization();
	void setBatteryMonitor(BatteryMonitor* batteryMonitor);
	void setProbeA(Probe* probe);
	//void setProbeA(HVProbe* probe);

	void propertyChanged(
				void* source,
				unsigned short int propertyId,
				const void* oldPropery);
	void actionPerformed(Action action);

protected:
	BatteryMonitor* batteryMonitor = nullptr;
	Probe* probeA = nullptr;
	//HVProbe* probeA = nullptr;
	NotificationSystem* notification = NotificationSystem::getInstance();
	RFTransceiver* transceiver = RFTransceiver::getInstance();

	void onProbeAMeasurementChanged(unsigned short int value);
	void onBatteryValueChanged(
				BatteryMonitor* source, short int value);
	void onBatteryTriggerAlarmStateChanged(
				BatteryMonitor* source, bool alarm);
	void onMessageReceived(char* msg);
	void onMessageSend(char* msg);
	void onConnectionStateChanged(bool state);
};

#endif /* CONTROLLER_H_ */
