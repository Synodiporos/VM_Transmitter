/*
 * SerialBroadcaster.h
 *
 *  Created on: 21 Ιουλ 2018
 *      Author: Synodiporos
 */

#ifndef SYSTEM_SERIALBROADCASTER_H_
#define SYSTEM_SERIALBROADCASTER_H_

class SerialBroadcaster {
public:
	virtual ~SerialBroadcaster();
	static SerialBroadcaster* getInstance();
	void validate();

private:
	SerialBroadcaster();
	static SerialBroadcaster* instance;
	String inputString;
	bool stringComplete = false;

	void onSerialMessageReceived();
};

#endif /* SYSTEM_SERIALBROADCASTER_H_ */
