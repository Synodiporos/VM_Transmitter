/*
 * Probe.h
 *
 *  Created on: 8 Αυγ 2018
 *      Author: Synodiporos
 */

#ifndef ANALOGINPUT_PROBE_H_
#define ANALOGINPUT_PROBE_H_

#include "Filters/FilterOnePole.h"
#include "../Commons/IPropertyListener.h"
#include "../System/SystemConstants.h"
#include <Arduino.h>

class Probe {
public:
	Probe(uint8_t pin, unsigned int rate);
	virtual ~Probe();
	void setEnabled(bool enabled);
	bool isEnabled();
	void setFrequency(float frequency);
	void setSamplingRate(unsigned int rate);
	float voltage(float vref, float offset);
	unsigned int getMeasurement();
	void setListener(IPropertyListener* listener);
	IPropertyListener* getListener();
	void validate();

private:
	uint8_t pin = 0;
	unsigned short int measurement = 0;
	FilterOnePole filter =  FilterOnePole(LOWPASS, 50);
	unsigned int rate = 64;
	unsigned long time = 0;
	bool filterEnabled = true;
	bool enabled = true;
	//uint8_t count = 0;
	IPropertyListener* listener = nullptr;
	//unsigned short int minMeasurement;
	//unsigned short int maxMeasurement;
	void setMeasurement(unsigned int measurement);
	void notifyMeasurementChanged(unsigned int oldMeas);

};

#endif /* ANALOGINPUT_PROBE_H_ */
