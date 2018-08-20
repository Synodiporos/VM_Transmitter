
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

BatteryMonitor* battery = BatteryMonitor::getInstance();
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

// the setup routine runs once when you press reset:
void setup() {
	pinMode(LED_WHITE_PIN, OUTPUT);
	pinMode(LED_RED_PIN, OUTPUT);
	pinMode(LED_BLUE_PIN, OUTPUT);
	pinMode(BUZZER_PIN, OUTPUT);

	Serial.begin(SRL_BD);
	Serial.println(F("SLAVE OK"));
	/*
	// initialize Timer1
	cli();          // disable global interrupts
	TCCR1A = 0;     // set entire TCCR1A register to 0
	TCCR1B = 0;     // same for TCCR1B
	// set compare match register to desired timer count:
	OCR1A = HVPROBE_TIMER_CYCLES; //198.4uS
	// turn on CTC mode:
	TCCR1B |= (1 << WGM12);
	// Set CS10 and CS12 bits for 1024 prescaler:
	TCCR1B |= (1 << CS10);
	TCCR1B |= (1 << CS12);
	// enable timer compare interrupt:
	TIMSK1 |= (1 << OCIE1A);
	sei();          // enable global interrupts
	*/


	/*cli(); // disable interrupt
	TCCR0A = 0;
	TCCR0B = 0;
	TCNT0 = 0; // initialize the counter from 0
	OCR0A = 255; // sets the counter compare value
	TCCR0A |= (1<<WGM01); // enable the CTC mode
	TCCR0B |= (1<<CS02);
	TCCR0B |= (1<<CS00); //sets the control scale bits for the timer
	TIMSK0 |= (1<<OCIE0A); //enable the interrupt
	sei(); //allows interrupts

*/

	probe.setFrequency(HVPROBE_FREQ);
	probe.setEnabled(true);

	//Initialaze RF
	trasnceiver->initialize(&radio);
	trasnceiver->setAutoSleep(true);
	//trasnceiver->printDetails();

	battery->startRecord();

	//hvProbe.startRecord();

	// Initialize Controller
	controller.setBatteryMonitor(battery);
	controller.setProbeA(&probe);
	//controller.setProbeA(&hvProbe);
	controller.activate();


	//delay(500);
	mil = millis();

	//string df("asd");
	//Serial.print("String");
	//Serial.println(df->c_str());
	//Serial.print("Size of fucking string:");
	//int size = sizeof(df);
	//Serial.println( size );

	/*int hvS = sizeof(hvProbe);
	Serial.print("Size of hvProbe:");
	Serial.println(hvS);

	int btS = sizeof(battery);
	Serial.print("Size of battery:");
	Serial.println(btS);

	int ctS = sizeof(controller);
	Serial.print("Size of controller:");
	Serial.println(ctS);*/

	//int ntS = sizeof(notification);
	//Serial.print("Size of notification:");
	//Serial.println(ntS);

	//Serial.print(F("@@ Free RAM Before CMD= ")); //F function does the same and is now a built in library, in IDE > 1.0.0
	//	Serial.println(freeMemory(), DEC);

	//CMDStartUp* startUp = new CMDStartUp();
	//startUp->execute();

	Serial.print(F("@@ Free RAM = ")); //F function does the same and is now a built in library, in IDE > 1.0.0
	Serial.println(freeMemory(), DEC);  // print how much RAM is available.
	// print how much RAM is available.
}

// the loop routine runs over and over again forever:
void loop() {
	long interval = millis()-mil;

	if(interval>=3000 && c==1){
		//c++;
		mil = millis();
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

	probe.validate();
	battery->validate();
	notification->validate();
	//serialBroad->validate();
	trasnceiver->validate();
	//executor->validate();

	//hvProbe.validate();
	//player.validate();
	//delay(10);
}

/*ISR(TIMER1_COMPA_vect){
	hvProbe.validate();
}*/

/*
ISR(TIMER0_COMPA_vect){
	//Serial.println("TT");

}*/
