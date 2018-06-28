/*
 * AnalogInput.h
 *
 *  Created on: Apr 20, 2018
 *      Author: sgeorgiadis
 */

#ifndef ANALOGINPUT_ANALOGINPUT_H_
#define ANALOGINPUT_ANALOGINPUT_H_
#include <stdint.h>
#include "../Commons/IPropertyListener.h"
#include "../Commons/Object.h"

class AnalogInput : public Object{
public:
	const static short int PROPERTY_ANALOG_VALUE = 20;

	AnalogInput(uint8_t pinNumber);
	AnalogInput(uint8_t pinNumber, uint8_t spv);
	virtual ~AnalogInput();

	void clearRecordsTable();
	uint8_t getPinNumber();
	unsigned short int getAnalogValue();
	void setPropertyListener(IPropertyListener * l);
	IPropertyListener* getPropertyListener();
	void validate();

protected:
	virtual void notifyPropertyChanged(unsigned long old);
	virtual void analogValueChanged(
				unsigned short int analogValue,
				unsigned short int old);
	unsigned short int _analogValue = 0;

private:
	uint8_t numReadings = 1;
	const uint8_t _pinNumber;
	unsigned long total = 0;
	unsigned short int * readings;
	uint8_t readIndex = 0;
	IPropertyListener * _listener = 0;


};

#endif /* ANALOGINPUT_ANALOGINPUT_H_ */
