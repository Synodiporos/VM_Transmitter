/*
 * RFTransceiver.h
 *
 *  Created on: 23 Ιουλ 2018
 *      Author: Synodiporos
 */

#ifndef DEVICES_RFTRANSCEIVER_H_
#define DEVICES_RFTRANSCEIVER_H_

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


class RFTransceiver {
public:
	RFTransceiver();
	virtual ~RFTransceiver();

	void begin();



private:
	uint8_t CE;
	uint8_t CSN;

	void onRFMessageReceived();

};

#endif /* DEVICES_RFTRANSCEIVER_H_ */
