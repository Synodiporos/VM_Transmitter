
#include <string>
#include <SPI.h>
#include "RF24.h"
using namespace std;
#include "libraries/LowPower/LowPower.h"
#include "System/SystemConstants.h"
#include "Devices/BatteryMonitor.h"
#include "Devices/Mosfet.h"
#include "Controller.h"
#include "System/NotificationSystem.h"
//#include "System/SerialBroadcaster.h"
#include "RFTransceiver/RFTransceiver.h"
#include "Memory/MemoryFree.h"
#include "Memory/pgmStrToRAM.h"
#include "Buzzer/BuzzerMelody.h"
#include "Buzzer/BuzzerTone.h"
#include "Buzzer/Pitches.h"


RF24 radio(RF_CE, RF_CSN);
Controller controller = Controller(radio);

long mil = millis();
int c = 1;
uint8_t flag = 3;

// the setup routine runs once when you press reset:
void setup() {

	/////////////////////////////////
	controller.activate();
	controller.onSystemStartUp();

	// Configure wake up pin as input.
	// This will consumes few uA of current.
	pinMode(WAKEUP_PIN, INPUT);



	mil = millis();
	Serial.print(F("@@ Free RAM = ")); //F function does the same and is now a built in library, in IDE > 1.0.0
	Serial.println(freeMemory(), DEC);  // print how much RAM is available.
	// print how much RAM is available.
}

// the loop routine runs over and over again forever:
void loop() {
	long interval = millis()-mil;
	if(interval>=3000 && c==1){
		//c++;
		//mil = millis();
		//Serial.println(F("SwitchOn Mosfet"));
		//mosfet->switchON();

		/*BuzzerTone* tone = new BuzzerTone(NOTE_A7, 25,
				new BuzzerTone(NOTE_BREAK, 75,
				new BuzzerTone(NOTE_C8, 25,
				new BuzzerTone(NOTE_BREAK, 75,
				new BuzzerTone(NOTE_C8, 25,
				new BuzzerTone(NOTE_BREAK, 700))))));*/
		//player.setHeadTone(tone);
		//player.play();

		//Serial.print(F("@@ Free RAM = ")); //F function does the same and is now a built in library, in IDE > 1.0.0
		//Serial.println(freeMemory(), DEC);
	}

	while(!controller.isSleep()){
		controller.onIterrate();
	}

	controller.onSystemSleep();
	//delay(50);
	flag = 0;
	// Allow wake up pin to trigger interrupt on low.
	attachInterrupt(0, onInterrupt, RISING);
	// Enter power down state with ADC and BOD module disabled.
	// Wake up when wake up pin is low.
	LowPower.powerDown(SLEEP_INTERVAL, ADC_OFF, BOD_OFF);

	// Disable external pin interrupt on wake up pin.
	detachInterrupt(0);

	if(flag==1){
	  controller.onSystemWakeup(SYSTEM_INTER);
	  flag = 3;
	}
	else if(flag==0){
	  flag = 3;
	  controller.onSystemWakeup(SYSTEM_TIMER);
	}
}

void onInterrupt(){
	if(flag!=1)
		flag = 1;
}

// ON SLEEP WITH RF DOWN: 300 nA
// ON WAKE UP WITH RF DOWN: 7.6 mA
// ON WAKE UP WITH RF ON: 24.4 mA
// AVERAGE 1.06 mA at 8 Seconds
