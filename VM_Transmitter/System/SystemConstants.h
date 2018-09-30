/*
 * SystemConstants.h
 *
 *  Created on: Jul 2, 2018
 *      Author: sgeorgiadis
 */

#ifndef SYSTEM_SYSTEMCONSTANTS_H_
#define SYSTEM_SYSTEMCONSTANTS_H_

//PIN NUMBER CONGIG
#define HV1_ANALOG_PIN (uint8_t) A1 //A1
#define HV2_ANALOG_PIN (uint8_t) A2 //A2
#define BT_ANALOG_PIN (uint8_t) A0 //A0
#define LED_RED_PIN 7
#define LED_BLUE_PIN 8
#define LED_WHITE_PIN 6
#define BUZZER_PIN 5
#define BUTTON_PIN (uint8_t) A3
#define MOSFET_PIN 4
#define RF_CE 9
#define RF_CSN 10
#define RF_IRQ 2
#define WAKEUP_PIN1 2
#define WAKEUP_PIN2 3
//SLEEP CONFIG
#define SLEEP_INTERVAL SLEEP_8S
#define WAKEUP_NORMAL 128
#define WAKEUP_WHEN_HV 4096
//REFERENCE VOLTAGE
#define AREF_VOLTAGE (float)3.299
//HV Probe CONFIG
#define HVPROBE_SPV (unsigned short int)16 // 32 Samples per Measurement
#define HVPROBE_UNITS (char*)"V"
#define HVPROBE_MIN_MEAS_RANGE (float)0
#define HVPROBE_MAX_MEAS_RANGE (float)40
#define HVPROBE_PERIOD 64
#define HVPROBE_FREQ (float)8
#define HVPROBE_VOLTS_OFFSET (float)0
//SURGE MONITOR
#define SM_SURGE_MIN 8
//10-350 CONFIG
#define FACTOR_10350 (float)0.0944756
//8-20 CONFIG
#define FACTOR_820 (float)1.0000000
//BATTERY CONFIG
#define BATTM_OFFSET (float)-0.00//0.2 //62 // 0.202V
#define BATTM_FACTOR (float)0.799
#define BATTM_DISC_VALUE (float)2.7 // 2.7V \\ At 2.61V worked fine
#define BATTM_FULL_VALUE (float)4.15 // 3.335V
#define BATTM_ALARM_VALUE (int)2.9175 // 15%
#define BATTM_HYSTERISIS_VALUE (int)0.029// 2%
#define BATTM_MEAS_PERIOD (int)256
#define BATTM_FREQ 0.0625 // 16 sec
#define BATTM_INTERVAL 100
#define BATTM_ITERS 2
//Serial
#define SRL_BD 115200
//RF CONFIG
#define RF_READ_PIPE (byte) 00001
#define RF_WRITE_PIPE (byte) 00002
#define RF_CC_PERIOD 11000
#define RF_CC_INTERVALS 200
#define RF_PD_PERIOD 1200
#define RF_PU_PERIOD 9500
#define RF_PAYLOAD_SIZE 24
#define RF_PALEVEL RF24_PA_LOW //RF24_PA_MIN = 0, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX,
#define RF_DATARATE RF24_250KBPS//RF24_1MBPS//RF24_250KBPS
//AT COMMANDS

#define CMD_HV1 "HV1"
#define CMD_SR1 "SR1"
#define CMD_HV2 "HV2"
#define CMD_SR2 "SR2"
#define CMD_BAT "BAT"
#define CMD_ACK "ACK"
#define CMD_ACR "ACR"
#define CMD_NTR "NTR"
#define CMD_SLP "SLP"
//NOTIFICATION CONFIG
//LED NOTIFICATION MODES
//ACTIVE
#define LED_M1 new LEDTone(3, 30,	\
		new LEDTone(255, 20, \
		new LEDTone(0, 0)))
//CONNECTION_LOST
#define LED_M3 new LEDTone(255, 25, \
		new LEDTone(0, 175, \
		new LEDTone(255, 50, \
		new LEDTone(0, 750))))
//HV_WARNING
#define LED_M5 new LEDTone(255, 25, \
		new LEDTone(0, 75, \
		new LEDTone(255, 25, \
		new LEDTone(0, 75, \
		new LEDTone(255, 50, \
		new LEDTone(0, 250 \
))))))
//BATTERY
#define LED_M6 new LEDTone(255, 50, \
		new LEDTone(0, 0 \
))
//ERROR
#define LED_M7 new LEDTone(255, 25,\
		new LEDTone(0, 75))

#define MELODY_HV new BuzzerTone(NOTE_A7, 250, \
		new BuzzerTone(NOTE_BREAK, 750 \
))

#endif /* SYSTEM_SYSTEMCONSTANTS_H_ */
