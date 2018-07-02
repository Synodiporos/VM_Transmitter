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
#include "VoltageMonitoring.h"

VoltageMonitoring monitor = VoltageMonitoring();

// the setup routine runs once when you press reset:
void setup() {

	// declare pin 9 to be an output:
	pinMode(HV_ANALOG_PIN, OUTPUT);


	// initialize Timer1
	cli();          // disable global interrupts
	TCCR1A = 0;     // set entire TCCR1A register to 0
	TCCR1B = 0;     // same for TCCR1B

	// set compare match register to desired timer count:
	OCR1A = 8;
	// turn on CTC mode:
	TCCR1B |= (1 << WGM12);
	// Set CS10 and CS12 bits for 1024 prescaler:
	TCCR1B |= (1 << CS10);
	TCCR1B |= (1 << CS12);
	// enable timer compare interrupt:
	TIMSK1 |= (1 << OCIE1A);
	sei();          // enable global interrupts
}

// the loop routine runs over and over again forever:
void loop() {

	//monitor.validate();
}

ISR(TIMER1_COMPA_vect){
    digitalWrite(LEDPIN, !digitalRead(LEDPIN));
}
