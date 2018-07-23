/*
 * NotificationSystem.h
 *
 *  Created on: Jul 4, 2018
 *      Author: sgeorgiadis
 */

#ifndef SYSTEM_NOTIFICATIONSYSTEM_H_
#define SYSTEM_NOTIFICATIONSYSTEM_H_
#include "SystemConstants.h"
#include "../LEDPlayer/LEDTone.h"
#include "../LEDPlayer/LEDTonePLayer.h"



class NotificationSystem {
public:
	NotificationSystem();
	virtual ~NotificationSystem();
	void initialize();

	void setHVWarningEnabled(bool enabled);
	void setBatteryLowEnabled(bool enabled);
	void setErrorEnabled(bool enabled);
	void setActiveEnabled(bool enabled);
	void setConnectionLostEnabled(bool enabled);
	void setTranferDataEnabled(bool enabled);
	void stopNotify();
	bool isHVWarningEnabled();
	bool isBatterLowEnabled();
	bool isErrorEnabled();
	bool isConnectionLostEnabled();
	bool isTranferDataEnabled();
	bool isActiveEnabled();
	void validate();

private:
	LEDTonePlayer ledWhite =
			LEDTonePlayer(LED_WHITE_PIN, nullptr, 0);
	LEDTonePlayer ledRed =
			LEDTonePlayer(LED_RED_PIN, nullptr, 0);
	LEDTonePlayer ledBlue =
			LEDTonePlayer(LED_BLUE_PIN, nullptr, 0);

	#define HV_WARNING 128
	#define BATTERY 64
	#define ERROR 32
	#define CONNECTION_LOST 16
	#define TRANSFER 8
	#define ACTIVE	4

	byte state = 00000000;

	LEDTone* active = LED_M1;
	LEDTone* hvWarning_white = LED_M2;
	LEDTone* hvWarning = LED_M5;
	LEDTone* battery = LED_M6;
	LEDTone* error = LED_M7;
	LEDTone* connectionLost = LED_M3;
	LEDTone* tranferData = LED_M4;


	void onStateChanged(byte change);
};

#endif /* SYSTEM_NOTIFICATIONSYSTEM_H_ */
