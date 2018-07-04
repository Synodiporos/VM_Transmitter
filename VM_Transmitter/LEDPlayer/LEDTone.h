/*
 * LEDTone.h
 *
 *  Created on: Jul 4, 2018
 *      Author: sgeorgiadis
 */

#ifndef LEDPLAYER_LEDTONE_H_
#define LEDPLAYER_LEDTONE_H_
#include <stdint.h>

class LEDTone {
public:
	LEDTone::LEDTone(int8_t frequency,
			unsigned short int duration) {
		setFrequency(frequency);
		setDuration(duration);
	}

	LEDTone(int8_t frequency,
			unsigned short int duration,
			LEDTone* next){
		setFrequency(frequency);
		setDuration(duration);
		setNextTone(next);
	}

	~LEDTone() {
		delete this->next;
	}

	void setFrequency(int8_t frequency){
		this->frequency = frequency;
	}

	int8_t getFrequency(){
		return this->frequency;
	}

	unsigned short int getDuration(){
		return this->duration;
	}

	void setDuration(unsigned short int duration){
		this->duration = duration;
	}

	void setNextTone(LEDTone* next){
		this->next = next;
	}

	LEDTone* getNextTone(){
		return this->next;
	}

	bool hasNext(){
		return this->next!=0;
	}

private:
	uint8_t frequency = 0;
	//Duration in Seconds.
	unsigned short int duration = 0;
	LEDTone* next = 0;

};

#endif /* LEDPLAYER_LEDTONE_H_ */
