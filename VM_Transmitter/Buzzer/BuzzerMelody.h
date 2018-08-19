/*
 * BuzzerMelody.h
 *
 *  Created on: 22 Απρ 2018
 *      Author: Synodiporos
 */

#ifndef BUZZER_BUZZERMELODY_H_
#define BUZZER_BUZZERMELODY_H_
#include <stdint.h>
#include "BuzzerTone.h"

class BuzzerMelody {
public:
	BuzzerMelody(uint8_t _pinNumber);
	BuzzerMelody(uint8_t _pinNumber, BuzzerTone* headTone);
	BuzzerMelody(uint8_t _pinNumber, BuzzerTone* headTone, short int iterations);
	virtual ~BuzzerMelody();

	void initialize();
	uint8_t getPinNumber();
	void setIterations(short int iterations);
	short int getIterations();
	void setHeadTone(BuzzerTone* headTone);
	uint8_t getState();
	BuzzerTone* getHeadTone();
	BuzzerTone* getCurrentTone();
	void play();
	void pause();
	void stop();
	void playTone(BuzzerTone* tone);
	void validate();

private:
	uint8_t _pinNumber = -1;
	BuzzerTone* _headTone = nullptr;
	short int _iterations = 1;
	//0=stop, 1=pause, 2=play
	uint8_t _state = 0;
	short int _performedIter = 0;
	unsigned long int _millis = 0;
	unsigned short int _interval = 0;
	BuzzerTone* _currentTone = _headTone;

	void playNextTone();
	void resumeFromCurrent();
	void playCurrentTone();
};

#endif /* BUZZER_BUZZERMELODY_H_ */
