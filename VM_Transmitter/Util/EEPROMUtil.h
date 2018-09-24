/*
 * EEPROMUtil.h
 *
 *  Created on: 24 Σεπ 2018
 *      Author: Synodiporos
 */

#ifndef UTIL_EEPROMUTIL_H_
#define UTIL_EEPROMUTIL_H_

#include <Arduino.h>
#include <EEPROM.h>

class EEPROMUtil {
public:
	EEPROMUtil();
	virtual ~EEPROMUtil();


	template <class T> static int writeStruct(
			int ee, const T& value);

	template <class T> static int readStruct(
			int ee, T& value);
};

#endif /* UTIL_EEPROMUTIL_H_ */
