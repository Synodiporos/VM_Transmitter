
#include "System/SystemConstants.h"
#include "Devices/BatteryMonitor.h"
#include "Controller.h"
#include "System/NotificationSystem.h"
#include "System/SerialBroadcaster.h"
#include "Memory/MemoryFree.h"
#include "Memory/pgmStrToRAM.h"
#include <string>
using namespace std;

/*HVProbe hvProbe = HVProbe(
		HV_ANALOG_PIN,
		HVPROBE_SPV,
		HVPROBE_BITRATE);

BatteryMonitor battery = BatteryMonitor(
		BT_ANALOG_PIN,
		BATTM_SPV,
		BATTM_MEAS_PERIOD,
		BATTM_ALARM_VALUE,
		BATTM_HYSTERISIS_VALUE,
		BATTM_DISC_VALUE,
		BATTM_FULL_VALUE);

Controller controller = Controller();

NotificationSystem notification = NotificationSystem();*/

SerialBroadcaster serialBroad = *SerialBroadcaster::getInstance();

long mil = millis();
int c = 1;


// the setup routine runs once when you press reset:
void setup() {
	pinMode(LED_WHITE_PIN, OUTPUT);
	pinMode(LED_RED_PIN, OUTPUT);
	pinMode(LED_BLUE_PIN, OUTPUT);
	digitalWrite(LED_WHITE_PIN, HIGH);
	digitalWrite(LED_RED_PIN, HIGH);
	digitalWrite(LED_BLUE_PIN, HIGH);

	Serial.begin(9600);
	Serial.println(F("OK"));

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

	// Initialize Controller
	/*controller.setHVProbe(&hvProbe);
	controller.setBatteryMonitor(&battery);
	controller.setNotificationSystem(&notification);*/
	//controller.activate();

	//hvProbe.startRecord();
	//battery.startRecord();

	delay(500);

	digitalWrite(LED_WHITE_PIN, LOW);
	digitalWrite(LED_RED_PIN, LOW);
	digitalWrite(LED_BLUE_PIN, LOW);

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

	Serial.print(F("Free RAM = ")); //F function does the same and is now a built in library, in IDE > 1.0.0
	Serial.println(freeMemory(), DEC);  // print how much RAM is available.
	// print how much RAM is available.
}

// the loop routine runs over and over again forever:
void loop() {
//	long interval = millis()-mil;

/*	if(interval>=5000 ){
		c++;
		mil = millis();
	}

	switch (c){
		case 1:{
			//Serial.println("-------------1");
			notification.setHVWarningEnabled(true);
			break;
		}
		case 2:{
			//Serial.println("-------------2");
			notification.setBatteryLowEnabled(true);
			break;
		}
		case 3:{
			//Serial.println("-------------3");
			notification.setErrorEnabled(true);
			break;
		}
		case 4:{
			//Serial.println("-------------3");
			notification.setHVWarningEnabled(false);
			break;
		}
		case 5:{
			//Serial.println("-------------3");
			notification.setBatteryLowEnabled(false);
			break;
		}
		case 6:{
			//Serial.println("-------------3");
			notification.setErrorEnabled(false);
			c = 0;
			break;
		}
	}*/

	/*hvProbe.validateTimer();
	hvProbe.validate();
	battery.validate();
	notification.validate();*/
	serialBroad.validate();
	//delay(10);
}

/*ISR(TIMER1_COMPA_vect){
	hvProbe.validate();
}*/

/*
ISR(TIMER0_COMPA_vect){
	//Serial.println("TT");

}*/
