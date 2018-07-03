/*
 * ToggleAnalogInput.h
 *
 *  Created on: Apr 20, 2018
 *      Author: sgeorgiadis
 */

#ifndef ANALOGINPUT_TOGGLEANALOGINPUT_H_
#define ANALOGINPUT_TOGGLEANALOGINPUT_H_
#include "AnalogInput.h"
#include "../Commons/IStateListener.h"
#include "../Commons/State.h"

class ToggleAnalogInput : public AnalogInput{
public:
	ToggleAnalogInput(uint8_t pinNumber);
	ToggleAnalogInput(uint8_t pinNumber, uint8_t spv);
	ToggleAnalogInput(uint8_t pinNumber, uint8_t spv,
				unsigned short int switchValue);
	ToggleAnalogInput(uint8_t pinNumber, uint8_t spv,
			unsigned short int switchValue,
			unsigned short int hysterisis);
	virtual ~ToggleAnalogInput();
	bool getToggleState();
	void setSwitchValue(unsigned short int switchValue);
	unsigned short int getSwitchValue();
	void setHysterisis(unsigned short int hysterisis);
	unsigned short int getHysterisis();
	void setStateListener(IStateListener * listener);
	IStateListener* getStateListener();

protected:
	bool state = false;
	unsigned short int switchValue = 0;
	unsigned short int hysterisis = 0;

	IStateListener * _stateListener = 0;

	virtual void onAnalogValueChanged(
					unsigned short int analogValue,
					unsigned short int old);
	void notifyToggleStateChanged();
};

#endif /* ANALOGINPUT_TOGGLEANALOGINPUT_H_ */
