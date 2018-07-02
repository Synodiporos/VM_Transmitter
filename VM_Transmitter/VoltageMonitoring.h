/*
 * VoltageMonitoring.h
 *
 *  Created on: Jul 2, 2018
 *      Author: sgeorgiadis
 */

#ifndef VOLTAGEMONITORING_H_
#define VOLTAGEMONITORING_H_
#include "../Devices/HVProbe.h";
#include "../System/SystemConstants.h"
#include "../Commons/IPropertyListener.h"

class VoltageMonitoring : IPropertyListener{
public:

	VoltageMonitoring();
	virtual ~VoltageMonitoring();

	void initialize();

	void propertyChanged(
				void* source,
				unsigned short int propertyId,
				const void* oldPropery);

	void validate();

private:
	HVProbe probe = HVProbe(HV_ANALOG_PIN, HVPROBE_SPV);
};

#endif /* VOLTAGEMONITORING_H_ */
