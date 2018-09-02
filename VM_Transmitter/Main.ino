
#include "libraries/LowPower/LowPower.h"

#include "System/SystemConstants.h"
#include "Devices/BatteryMonitor.h"
#include "Devices/Mosfet.h"
#include "Devices/HVProbe.h"
#include "Controller.h"
#include "System/NotificationSystem.h"
#include "System/SerialBroadcaster.h"
#include "RFTransceiver/RFTransceiver.h"
#include "Memory/MemoryFree.h"
#include "Memory/pgmStrToRAM.h"
//#include "CMD/CMD.h"
//#include "CMD/CMDStartUp.h"
#include "AnalogInput/Probe.h"

#include "Buzzer/BuzzerMelody.h"
#include "Buzzer/BuzzerTone.h"
#include "Buzzer/Pitches.h"

#include <SPI.h>
#include <RF24.h>
#include <string>
using namespace std;

BatteryMonitor* battery;
Probe probe = Probe(HV_ANALOG_PIN, HVPROBE_PERIOD);
//HVProbe hvProbe = HVProbe(HV_ANALOG_PIN, HVPROBE_SPV, HVPROBE_PERIOD);
Mosfet* mosfet = Mosfet::getInstance();
Controller controller = Controller();
NotificationSystem* notification = NotificationSystem::getInstance();
SerialBroadcaster* serialBroad = SerialBroadcaster::getInstance();
RFTransceiver* trasnceiver = RFTransceiver::getInstance();
//CMDExecutor* executor = CMDExecutor::getInstance();
RF24 radio(RF_CE, RF_CSN);
BuzzerMelody player =
			BuzzerMelody(BUZZER_PIN, nullptr, 0);

long mil = millis();
int c = 1;
uint8_t flag = 3;

// the setup routine runs once when you press reset:
void setup() {
	pinMode(LED_WHITE_PIN, OUTPUT);
	pinMode(LED_RED_PIN, OUTPUT);
	pinMode(LED_BLUE_PIN, OUTPUT);
	pinMode(BUZZER_PIN, OUTPUT);

	Serial.begin(SRL_BD);
	Serial.println(F("SLAVE OK"));

	probe.setFrequency(HVPROBE_FREQ);
	probe.setEnabled(true);

	//Initialaze RF
	trasnceiver->initialize(&radio);
	trasnceiver->setAutoSleep(true);
	//trasnceiver->printDetails();

	battery = BatteryMonitor::getInstance();
	//battery->startRecord();

	// Initialize Controller
	controller.setBatteryMonitor(battery);
	controller.setProbeA(&probe);
	//controller.setProbeA(&hvProbe);
	controller.activate();


	/////////////////////////////////
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

	/*probe.validate();
	battery->validate();
	notification->validate();
	trasnceiver->validate();*/

	//serialBroad->validate();
	//executor->validate();

	//hvProbe.validate();
	//player.validate();
	//delay(10);



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

