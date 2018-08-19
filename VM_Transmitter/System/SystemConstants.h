/*
 * SystemConstants.h
 *
 *  Created on: Jul 2, 2018
 *      Author: sgeorgiadis
 */

#ifndef SYSTEM_SYSTEMCONSTANTS_H_
#define SYSTEM_SYSTEMCONSTANTS_H_

//PIN NUMBER CONGIG
#define HV_ANALOG_PIN (uint8_t) A1 //A1
#define BT_ANALOG_PIN (uint8_t) A0 //A0
#define LED_RED_PIN 8
#define LED_BLUE_PIN 7
#define LED_WHITE_PIN 6
#define BUZZER_PIN 5
#define BUTTON_PIN 3
#define MOSFET_PIN 4
#define RF_CE 9
#define RF_CSN 10
#define RF_IRQ 2
//REFERENCE VOLTAGE
#define AREF_VOLTAGE (float)3.297
//HV Probe CONFIG
#define HVPROBE_SPV (unsigned short int)16 // 32 Samples per Measurement
#define HVPROBE_UNITS (char*)"V"
#define HVPROBE_MIN_MEAS_RANGE (float)0
#define HVPROBE_MAX_MEAS_RANGE (float)45
#define HVPROBE_PERIOD 128
#define HVPROBE_FREQ (float)0.5
#define HVPROBE_VOLTS_OFFSET (float)0
//10-350 CONFIG
#define FACTOR_10350 0.11367
//BATTERY CONFIG
#define BATTM_OFFSET 17 //Vdrop = 56mV, 180mV
#define BATTM_DISC_VALUE (int)828 // 2.7V \\ At 2.61V worked fine
#define BATTM_FULL_VALUE (int)1020 // 3.335V
#define BATTM_ALARM_VALUE (int)846 // 2.76V
#define BATTM_HYSTERISIS_VALUE (int)10// 2.792V - 0.0326v
#define BATTM_MEAS_PERIOD (int)1024
#define BATTM_FREQ 0.1
//Serial
#define SRL_BD 115200
//RF CONFIG
#define RF_READ_PIPE (byte) 00001
#define RF_WRITE_PIPE (byte) 00002
#define RF_CC_PERIOD 11000
#define RF_CC_INTERVALS 500
#define RF_PD_PERIOD 1200
#define RF_PU_PERIOD 9500
#define RF_PAYLOAD_SIZE 16
//AT COMMANDS
#define CMD_HV1 "HV1"
#define CMD_SR1 "SR1"
#define CMD_HV2 "HV2"
#define CMD_SR2 "SR2"
#define CMD_BAT "BAT"
#define CMD_ACK "ACK"
#define CMD_ACR "ACR"
//NOTIFICATION CONFIG
#define NOT_HVWARNING_TRIG 6
//LED NOTIFICATION MODES
//ACTIVE
#define LED_M1 new LEDTone(3, 40,	\
		new LEDTone(255, 20, \
		new LEDTone(0, 2940)))
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
#define LED_M5 new LEDTone(255, 25, \
		new LEDTone(0, 75, \
		new LEDTone(255, 25, \
		new LEDTone(0, 75, \
		new LEDTone(255, 25, \
		new LEDTone(0, 75, \
		new LEDTone(255, 25, \
		new LEDTone(0, 75, \
		new LEDTone(255, 75, \
		new LEDTone(0, 25 \
))))))))))
//BATTERY
#define LED_M6 new LEDTone(255, 50, \
		new LEDTone(0, 1950 \
))
//ERROR
#define LED_M7 new LEDTone(255, 250,\
		new LEDTone(0, 500))


#define MELODY_HV new BuzzerTone(NOTE_A7, 100, \
		new BuzzerTone(NOTE_C8, 400, \
		new BuzzerTone(NOTE_BREAK, 500 \
)))

#endif /* SYSTEM_SYSTEMCONSTANTS_H_ */
