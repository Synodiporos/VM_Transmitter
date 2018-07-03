/*
 * SystemConstants.h
 *
 *  Created on: Jul 2, 2018
 *      Author: sgeorgiadis
 */

#ifndef SYSTEM_SYSTEMCONSTANTS_H_
#define SYSTEM_SYSTEMCONSTANTS_H_


#define HV_ANALOG_PIN (uint8_t) A1 //Á1
#define BT_ANALOG_PIN (uint8_t) A0 //Á0

#define HVPROBE_SPV (unsigned short int)32
#define HVPROBE_UNITS (char*)"kV"
#define HVPROBE_MIN_RANGE (float)0
#define HVPROBE_MAX_RANGE (float)3.77
#define HVPROBE_MIN_MEAS_RANGE (float)0
#define HVPROBE_MAX_MEAS_RANGE (float)45
#define HVPROBE_BITRATE 128

#define BATTM_DISC_VOLTAGE 3.0
#define BATTM_FULL_VOLTAGE 4.2
#define BATTM_MIN_RANGE (float)0
#define BATTM_MAX_RANGE (float)3.77
#define BATTM_BITRATE 1024
#define BATTM_SPV (unsigned short int)32


#endif /* SYSTEM_SYSTEMCONSTANTS_H_ */
