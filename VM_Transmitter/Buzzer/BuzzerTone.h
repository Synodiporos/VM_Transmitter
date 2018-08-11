/*
 * BuzzerTone.h
 *
 *  Created on: 29 Μαρ 2018
 *      Author: Synodiporos
 */

#ifndef BUZZER_BUZZERTONE_H_
#define BUZZER_BUZZERTONE_H_

class BuzzerTone {
public:
	BuzzerTone(unsigned short int frequency, unsigned short int duration);
	BuzzerTone(unsigned short int tone, unsigned short int duration,
			BuzzerTone* next);
	virtual ~BuzzerTone();

	void setFrequency(unsigned short int frequency);
	unsigned short int getFrequency();
	void setDuration(unsigned short int duration);
	unsigned short int getDuration();
	void setNextTone(BuzzerTone* next);
	BuzzerTone* getNextTone();
	bool hasNext();

private:
	unsigned short int frequency = 0;
	//Duration in Seconds.
	unsigned short int duration = 0;

	BuzzerTone* next = 0;
};

#endif /* BUZZER_BUZZERTONE_H_ */
