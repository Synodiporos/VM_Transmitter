/*
 Fade

 This example shows how to fade an LED on pin 9
 using the analogWrite() function.

 The analogWrite() function uses PWM, so if
 you want to change the pin you're using, be
 sure to use another PWM capable pin. On most
 Arduino, the PWM pins are identified with 
 a "~" sign, like ~3, ~5, ~6, ~9, ~10 and ~11.

 This example code is in the public domain.
 */
#include "System/SystemConstants.h"
#include "Devices/BatteryMonitor.h"
#include "Controller.h"
#include "System/NotificationSystem.h"

//VoltageMonitoring monitor = VoltageMonitoring();
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

	pinMode(LED_WHITE_PIN, OUTPUT);
	pinMode(LED_RED_PIN, OUTPUT);

	analogWrite(LED_WHITE_PIN, 100);
	analogWrite(LED_RED_PIN, 128);

	Serial.println("Transmitter Started!");
	//delay(1000);
}

// the loop routine runs over and over again forever:
void loop() {

	//monitor.validate();
	hvProbe.validateTimer();
	hvProbe.validate();
	battery.validate();
	notification.validate();
	delay(1);
}

/*ISR(TIMER1_COMPA_vect){
	hvProbe.validate();
}*/

ISR(TIMER0_COMPA_vect){
	//Serial.println("TT");

}
