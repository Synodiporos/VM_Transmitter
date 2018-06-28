/*
 * AnalogMeasurement.h
 *
 *  Created on: Jun 21, 2018
 *      Author: sgeorgiadis
 */

#ifndef ANALOGINPUT_ANALOGMEASUREMENT_H_
#define ANALOGINPUT_ANALOGMEASUREMENT_H_

#include "AnalogInput.h"

class AnalogMeasurement: public AnalogInput {
public:
	AnalogMeasurement(uint8_t pinNumber);
	AnalogMeasurement(uint8_t pinNumber, uint8_t spv);
	AnalogMeasurement(uint8_t pinNumber, uint8_t spv, float coef);
	AnalogMeasurement(uint8_t pinNumber, uint8_t spv,
			float min, float max, char* units);
	virtual ~AnalogMeasurement();

	void setLimits(float min, float max);
	float getMin();
	float getMax();
	void setUnits(char* units);
	char* getUnits();
	float getMeasurement();
	static int coefficient(float realMaxValue);
	long map(long x, long out_min, long out_max);

private:
	float min = 0;
	float max = 0;
	char* units = nullptr;
};

#endif /* ANALOGINPUT_ANALOGMEASUREMENT_H_ */
