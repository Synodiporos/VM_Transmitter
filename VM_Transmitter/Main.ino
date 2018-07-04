
#include "System/SystemConstants.h"
#include "Devices/BatteryMonitor.h"
#include "Controller.h"
#include "System/NotificationSystem.h"


HVProbe hvProbe = HVProbe(
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

NotificationSystem notification = NotificationSystem();

// the setup routine runs once when you press reset:
void setup() {
	pinMode(LED_WHITE_PIN, OUTPUT);
	pinMode(LED_RED_PIN, OUTPUT);
	digitalWrite(LED_WHITE_PIN, HIGH);
	digitalWrite(LED_RED_PIN, HIGH);

	Serial.begin(9600);
	Serial.println("Transmitter Starting...");

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
	controller.setHVProbe(&hvProbe);
	controller.setBatteryMonitor(&battery);
	controller.setNotificationSystem(&notification);
	controller.activate();

	//hvProbe.startRecord();
	//battery.startRecord();

	delay(500);
	Serial.println("Transmitter Started!");

	digitalWrite(LED_WHITE_PIN, LOW);
	digitalWrite(LED_RED_PIN, LOW);
}

// the loop routine runs over and over again forever:
void loop() {

	hvProbe.validateTimer();
	hvProbe.validate();
	battery.validate();

	notification.validate();
	//delay(1);
}

/*ISR(TIMER1_COMPA_vect){
	hvProbe.validate();
}*/

/*
ISR(TIMER0_COMPA_vect){
	//Serial.println("TT");

}*/
