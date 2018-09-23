/*
 * Controller.h
 *
 *  Created on: Jul 4, 2018
 *      Author: sgeorgiadis
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_
#include <SPI.h>
#include <RF24.h>
#include "Commons/IActionListener.h"
#include "Commons/Action.h"
#include "Commons/IPropertyListener.h"
#include "Commons/IStateListener.h"
#include "Commons/IActionListener.h"
#include "Commons/Action.h"
#include "Devices/BatteryMonitor.h"
#include "Devices/IBatteryMonitorListener.h"
#include "Devices/SurgeMonitor.h"
#include "Devices/Mosfet.h"
#include "AnalogInput/Probe.h"
#include "System/SystemConstants.h"
#include "System/NotificationSystem.h"
#include "RFTransceiver/RFTransceiver.h"
#include "Util/CharUtil.h"
#include <string>

#define SYSTEM_TIMER 1
#define SYSTEM_INTER 2

class Controller : public IBatteryMonitorListener,
	IPropertyListener, IActionListener{
public:
	Controller(RF24& radio);
	virtual ~Controller();

	void activate();
	void deactivate();
	void initialization();

	void propertyChanged(
				void* source,
				unsigned short int propertyId,
				const void* oldPropery);
	void actionPerformed(Action action);

	bool isSleep();
	void onSystemStartUp();
	void onSystemSleep();
	void onSystemWakeup(uint8_t source);
	void onIterrate();

protected:
	RF24& radio ;
	BatteryMonitor* batteryMonitor = BatteryMonitor::getInstance();;
	Probe probeA = Probe(HV1_ANALOG_PIN, HVPROBE_PERIOD);
	Probe probeB = Probe(HV2_ANALOG_PIN, HVPROBE_PERIOD);
	SurgeMonitor surgeMonitor;
	Mosfet* mosfet = Mosfet::getInstance();
	RFTransceiver* transceiver = RFTransceiver::getInstance(radio);
	NotificationSystem* notification = NotificationSystem::getInstance();

	bool hvWarning = false;
	bool sleep = false;
	unsigned long sleepTimer = millis();
	unsigned long timer2 = millis();


	void resetSleepTimer();
	void onProbeAMeasurementChanged(unsigned short int value);
	void onProbeBMeasurementChanged(unsigned short int value);
	void onSurgeApplied(uint8_t device,
			unsigned int charge, unsigned int slope);
	void onBatteryValueChanged(
				BatteryMonitor* source, short int value);
	void onBatteryTriggerAlarmStateChanged(
				BatteryMonitor* source, bool alarm);
	void onRFStateChanged(uint8_t action, uint8_t state);
	void onRFMessageReceived(char* msg);
	void onRFResponseReceived(char* msg, uint8_t id);
	void onRFMessageSend(char* msg);
	void onRFMessageSendError(char* msg);

};

#endif /* CONTROLLER_H_ */
