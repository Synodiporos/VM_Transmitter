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
#include "../System/SystemConstants.h"

class HVProbe : public AnalogInput, IActionListener{
public:
	//static const short int MEASUREMENT_CHANGED = 1;
	static const short int HVP_MEASUREMENT_PROPERTY = 10;

	HVProbe();
	HVProbe(uint8_t pinNumber);
	HVProbe(uint8_t pinNumber, uint8_t spv);
	HVProbe(uint8_t pinNumber, uint8_t spv,
			unsigned short int period);
	virtual ~HVProbe();
	void initialize();
	void startRecord();
	void pauseRecord();
	void stopRecord();

	float getMeasurement();
	float getVoltage(float VREF);

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
	Timer timer = Timer(HVPROBE_PERIOD, 0);
	unsigned short int oldAnalogValue = 0;
	IPropertyListener* measurementListener = nullptr;
};

#endif /* DEVICES_HVPROBE_H_ */
