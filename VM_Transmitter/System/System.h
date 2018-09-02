/*
 * System.h
 *
 *  Created on: 28 Αυγ 2018
 *      Author: Synodiporos
 */

#ifndef SYSTEM_SYSTEM_H_
#define SYSTEM_SYSTEM_H_

#include <stdint.h>
//using namespace std;

#define SYSTEM_TIMER 1;
#define SYSTEM_INTER 2;

class System {
public:

	virtual ~System();

	void onSystemStartUp();
	void onSystemSleep();
	void onSystemWakeup(uint8_t source);
	void onIterrate();

private:
	System();


};

#endif /* SYSTEM_SYSTEM_H_ */
