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


#define LED_M1_T1 LEDTone(255, 25)
#define LED_M1_T2 LEDTone(0, 75)
#define LED_M1_T3 LEDTone(255, 25)
#define LED_M1_T4 LEDTone(0, 75)
#define LED_M1_T5 LEDTone(255, 25)
#define LED_M1_T6 LEDTone(0, 2775)

#define LED_M2_T1 LEDTone(255, 25)
#define LED_M2_T2 LEDTone(0, 75)
#define LED_M2_T3 LEDTone(255, 25)
#define LED_M2_T4 LEDTone(0, 75)
#define LED_M2_T5 LEDTone(255, 25)
#define LED_M2_T6 LEDTone(0, 2775)

#endif /* SYSTEM_SYSTEMCONSTANTS_H_ */
