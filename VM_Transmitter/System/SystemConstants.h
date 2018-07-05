/*
 * SystemConstants.h
 *
 *  Created on: Jul 2, 2018
 *      Author: sgeorgiadis
 */

#ifndef SYSTEM_SYSTEMCONSTANTS_H_
#define SYSTEM_SYSTEMCONSTANTS_H_


#define HV_ANALOG_PIN (uint8_t) A1 //A1
#define BT_ANALOG_PIN (uint8_t) A0 //A0
#define LED_BLUE_PIN 6
#define LED_RED_PIN 9
#define LED_WHITE_PIN 10

#define AREF_VOLTAGE 3.794

#define HVPROBE_SPV (unsigned short int)32 // 32
#define HVPROBE_TIMER_CYCLES (unsigned short int)61 // 61
#define HVPROBE_UNITS (char*)"kV"
#define HVPROBE_MIN_MEAS_RANGE (float)0
#define HVPROBE_MAX_MEAS_RANGE (float)45
#define HVPROBE_BITRATE 128

#define BATTM_DISC_VALUE 814 // 3.0V
#define BATTM_FULL_VALUE 977 // 3.6V
#define BATTM_ALARM_VALUE 838 // 3.09V
#define BATTM_HYSTERISIS_VALUE 3// 3.102V - 0.02v
#define BATTM_MEAS_PERIOD 1024
#define BATTM_SPV 16

//ACTIVE
#define LED_M1 new LEDTone(255, 25,	\
		new LEDTone(0, 2975))
//CONNECTION_LOST
#define LED_M3 new LEDTone(255, 50, \
		new LEDTone(0, 950))
//TRANSFER
#define LED_M4_ITER 1;
#define LED_M4 new LEDTone(255, 25, \
		new LEDTone(0, 75, \
		new LEDTone(255, 25, \
		new LEDTone(0, 2775 \
))))
//HV_WARNING
#define LED_M5 new LEDTone(255, 75, \
		new LEDTone(0, 25, \
		new LEDTone(255, 75, \
		new LEDTone(0, 25, \
		new LEDTone(255, 75, \
		new LEDTone(0, 25, \
		new LEDTone(255, 25, \
		new LEDTone(0, 75, \
		new LEDTone(255, 25, \
		new LEDTone(0, 75, \
		new LEDTone(255, 25, \
		new LEDTone(0, 400 \
))))))))))))
//BATTERY
#define LED_M2 new LEDTone(255, 25, \
		new LEDTone(0, 75, \
		new LEDTone(255, 50, \
		new LEDTone(0, 1850 \
))))
//ERROR
#define LED_M6 new LEDTone(255, 750,\
		new LEDTone(0, 750))


#endif /* SYSTEM_SYSTEMCONSTANTS_H_ */
