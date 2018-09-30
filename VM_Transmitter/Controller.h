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
#include "Commons/State.h"
#include "Commons/IActionListener.h"
#include "Commons/Action.h"
#include "Devices/BatteryMonitor.h"
#include "Devices/IBatteryMonitorListener.h"
#include "Devices/SurgeMonitor.h"
#include "Devices/Mosfet.h"
#include "AnalogInput/Probe.h"
#include "Button/Button.h"
#include "System/SystemConstants.h"
#include "System/NotificationSystem.h"
#include "System/PersistBuffer.h"
#include "System/UnixTime.h"
#include "RFTransceiver/RFTransceiver.h"
#include "Util/CharUtil.h"
#include <string>

#define SYSTEM_TIMER 1
#define SYSTEM_INTER 2

class Controller : public IBatteryMonitorListener,
	IPropertyListener, IActionListener, IStateListener{
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
	void stateChanged(State state);

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
	Button button = Button(BUTTON_PIN);
	RFTransceiver* transceiver = RFTransceiver::getInstance(radio);
	NotificationSystem* notification = NotificationSystem::getInstance();
	PersistBuffer* buffer = PersistBuffer::getInstance();

	unsigned int HV1 = 0;
	unsigned long HV2 = 0;
	bool HVWARNING = false;
	bool SLEEP = false;
	unsigned int WAKEUP_DURATION = WAKEUP_NORMAL;
	unsigned long sleepTimer = millis();
	unsigned long bufferTimer = millis();
	unsigned long timer2 = millis();
	uint8_t requestId = 1;
	Surge surge;
	uint8_t surgePostState = 0;
	//0 buffer 0:OK 1:NOT SEND 2:SEND 3:NOT POSTED 4:POSTED
	//1	Live   		11:NOT SEND	12:SEND 13:NOT POSTED 14:POSTED

	uint8_t getRequestId();
	void resetSleepTimer();
	uint8_t sendSurgeRequest(Surge surge, uint8_t source);
	void onSurgeRequestStateChanged(uint8_t state);
	void onProbeAMeasurementChanged(unsigned short int value);
	void onProbeBMeasurementChanged(unsigned short int value);
	void onHVWarningStateChanged(bool state);
	void onSurgeApplied(Surge surge);
	void onBatteryValueChanged(
				BatteryMonitor* source, short int value);
	void onBatteryTriggerAlarmStateChanged(
				BatteryMonitor* source, bool alarm);
	void onRFStateChanged(uint8_t action, uint8_t state);
	void onRFMessageReceived(char* msg);
	void onRFResponseReceived(char* msg, uint8_t id);
	void onRFMessageSend(char* msg);
	void onRFMessageSendError(char* msg);
	void onRFRequestPostOK(char* msg, uint8_t id);
	void onRFRequestPostFail(char* msg, uint8_t id);
	void onButtonStateChanged(ButtonState state);

};

#endif /* CONTROLLER_H_ */
