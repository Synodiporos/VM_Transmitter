/*
 * EEPROMUtil.cpp
 *
 *  Created on: 24 Σεπ 2018
 *      Author: Synodiporos
 */

#include "EEPROMUtil.h"

EEPROMUtil::EEPROMUtil() {
	// TODO Auto-generated constructor stub

}

EEPROMUtil::~EEPROMUtil() {
	// TODO Auto-generated destructor stub
}

template <class T> int EEPROMUtil::writeStruct(int ee, const T& value)
{
    const byte* p = (const byte*)(const void*)&value;
    unsigned int i;
    for (i = 0; i < sizeof(value); i++)
          EEPROM.write(ee++, *p++);
    return i;
}

template <class T> int EEPROMUtil::readStruct(int ee, T& value)
{
    byte* p = (byte*)(void*)&value;
    unsigned int i;
    for (i = 0; i < sizeof(value); i++)
          *p++ = EEPROM.read(ee++);
    return i;
}
