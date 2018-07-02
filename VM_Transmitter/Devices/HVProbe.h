/*
 * HVProbe.h
 *
 *  Created on: Jul 2, 2018
 *      Author: sgeorgiadis
 */

#ifndef DEVICES_HVPROBE_H_
#define DEVICES_HVPROBE_H_
#include "../AnalogInput/AnalogInput.h"
#include "../Commons/IActionListener.h"
#include "../Timer/Timer.h"
#include "../Math/MathUtil.h"

class HVProbe : public AnalogInput, IActionListener{
public:
	static const short int MEASUREMENT_CHANGED = 1;
	static const short int MEASUREMENT_PROPERTY = 10;

	HVProbe();
	HVProbe(uint8_t pinNumber);
	HVProbe(uint8_t pinNumber, uint8_t spv);
	HVProbe(uint8_t pinNumber, uint8_t spv,
			unsigned short int bitrate);
	virtual ~HVProbe();
	void initialize();

	float getMeasurement();
	void setUnit(char* units);
	char* getUnits();
	void setRange(float min, float max);

	void setMeasurementListener(IPropertyListener* listener);
	IPropertyListener* getMeasurementListener();
	void notifyMeasurementChanged();

	void actionPerformed(Action action);
	virtual void analogValueChanged(
					unsigned short int analogValue,
					unsigned short int old);

	void validate();
	void validateTimer();

private:
	char* units = nullptr;
	float minValue = 0;
	float maxValue = 1023;
	Timer timer = Timer(128, 0, MEASUREMENT_CHANGED);
	unsigned short int oldAnalogValue = 0;
	IPropertyListener* measurementListener = nullptr;
};

#endif /* DEVICES_HVPROBE_H_ */
