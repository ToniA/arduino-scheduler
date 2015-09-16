/*
 * by Ozan Oner
 * Scheduler for repeating tasks
 * Based on Simon Monk's Timer
 * http://playground.arduino.cc/Code/Timer
 *
 */

#ifndef EVENT_H
#define EVENT_H

#include "Arduino.h"
#include "SchedulerClient.h"

class Event {
public:
	enum EventType {
		NONE,
		EVERY,
		OSCILLATE
	};

	Event(byte id);

	// call in loop
	void update(void);

	void stop() { this->eventType = Event::NONE; };
	EventType getEventType() const { return this->eventType; };

	int every(SchedulerClient* cl, unsigned long period, \
			int repeatCount);

	int oscillate(byte pin, unsigned long period, 
			byte startValue, int repeatCount);
private:
	byte id;

	EventType eventType;
	unsigned long period;
	unsigned long next;
	int repeatCount;

	SchedulerClient* client;
	byte pin;
	byte pinState;

	void setNext(unsigned long);
	void reset();
};

#endif
