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

	void notifyActive();
	void notifyWarning();
	void stopNotify();

	void validate();


	LEDTonePlayer ledMode_active =
			LEDTonePlayer(LED_WHITE_PIN, nullptr, 3);
	LEDTonePlayer ledMode_warning =
				LEDTonePlayer(LED_RED_PIN, nullptr, 0);

};

#endif /* SYSTEM_NOTIFICATIONSYSTEM_H_ */
