/*
 * PersistBuffer.h
 *
 *  Created on: 24 Σεπ 2018
 *      Author: Synodiporos
 */

#ifndef SYSTEM_PERSISTBUFFER_H_
#define SYSTEM_PERSISTBUFFER_H_

#include <Arduino.h>
#include <EEPROM.h>
#include "../Devices/SurgeMonitor.h"
#include "../Util/EEPROMUtil.h"

#define PB_START_INDEX 317
#define PB_CAPACITY 64

class PersistBuffer {
public:
	PersistBuffer();
	virtual ~PersistBuffer();
	void initialize();
	uint8_t getSize();
	bool isEmpty();
	uint8_t push(Surge &surge);
	uint8_t getAt(uint8_t index, Surge& surge);
	uint8_t top(Surge &surge);
	uint8_t pop();
	void clear();
	void print();

private:
	uint8_t index = 0;
	uint8_t size = 0;

	bool setIndex(uint8_t index);
	bool setSize(uint8_t size);
	void onIndexChanged();
	void onSizeChanged();
	uint8_t write(uint8_t index, Surge &surge);
	uint8_t read(uint8_t index, Surge &surge);
};

#endif /* SYSTEM_PERSISTBUFFER_H_ */
