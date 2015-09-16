
#include <Arduino.h>
#include <Scheduler.h>
#include "SchedulerClient2.h"

// use onboard Arduino LED to test oscillate
#define LED_PIN 13


// a derived SchedulerClient
SchedulerClient2 *cl2 = new SchedulerClient2();
// A SchedulerClient which wraps cb1
SchedulerClient cl1(cb1);

// Scheduler instance
Scheduler s;

void setup() {
	Serial.begin(9600);

	// 'every' test with ordinary function
	if(s.every(&cl1, 1000)<0)
		printFail("--1");
	// 'every' test with member function 
	if(s.every(cl2, 3000)<0)
		printFail("--2");
	// 'every' test for repeatCount & schedulerEnded 
	if(s.every(cl2, 2000, 3)<0)
		printFail("--3");

	// 'oscillate' test over LED
	if(s.oscillate(LED_PIN, 1000, HIGH)<0)
		printFail("--4");
	
	// consume all events
	for(int i=0; i<10; i++) {
		if(s.every(cl2, 1000, 2)<0) {
			printFail("");
			Serial.println(i);
		}
	}
}

void loop() {
	s.update();
}

void cb1(int id) {
	Serial.print("Callback from event (cl1): ");
	Serial.println(id);
}

void printFail(const char* mess) {
	Serial.print("Failed: ");
	Serial.println(mess);
}
