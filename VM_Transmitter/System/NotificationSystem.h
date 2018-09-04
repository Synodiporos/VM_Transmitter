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
#include "../Buzzer/BuzzerMelody.h"
#include "../Buzzer/BuzzerTone.h"
#include "../Buzzer/Pitches.h"

#define HV_WARNING 128
#define BATTERY 64
#define ERROR 32
#define CONNECTION_LOST 16
#define TRANSFER 8
#define ACTIVE	4

class NotificationSystem {
public:
	static NotificationSystem* getInstance();
	virtual ~NotificationSystem();
	void initialize();
	bool setEnabled(bool enabled);
	bool isEnabled();

	void setHVWarningEnabled(bool enabled);
	void setBatteryLowEnabled(bool enabled);
	void setErrorEnabled(bool enabled);
	void setActiveEnabled(bool enabled);

	void startNotify();
	void stopNotify();

	void validateChanges();

	void setConnectionLostEnabled(bool enabled);
	void setTranferDataEnabled(bool enabled);
	void setMelody(BuzzerTone* tone);
	bool isHVWarningEnabled();
	bool isBatterLowEnabled();
	bool isErrorEnabled();
	bool isConnectionLostEnabled();
	bool isTranferDataEnabled();
	bool isActiveEnabled();
	void validate();

private:
	static NotificationSystem* instance;
	bool enable = false;
	byte state = 00000000;

	LEDTone* LTActive = LED_M1;
	LEDTone* LTHVWarning = LED_M5;
	LEDTone* LTBatteryWarning = LED_M6;
	LEDTone* LTError = LED_M7;
	LEDTone* LTConnLost = LED_M3;
	BuzzerTone* BTHVWarning = MELODY_HV;

	LEDTonePlayer ledWhite =
			LEDTonePlayer(LED_BLUE_PIN, LTActive, 1);
	LEDTonePlayer ledRed =
			LEDTonePlayer(LED_RED_PIN, nullptr, 0);
	//LEDTonePlayer ledBlue =
	//		LEDTonePlayer(LED_BLUE_PIN, nullptr, 0);
	BuzzerMelody player =
			BuzzerMelody(BUZZER_PIN, BTHVWarning, 0);


	NotificationSystem();
	void onStateChanged(byte change);
};

#endif /* SYSTEM_NOTIFICATIONSYSTEM_H_ */
