
/*
 * by Ozan Oner
 * Scheduler for repeating tasks
 *
 * Based on Simon Monk's Timer
 * http://playground.arduino.cc/Code/Timer
 *
 */

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "Arduino.h"
#include "SchedulerClient.h"
#include "Event.h"

#define SCH_MAX_EVENT 10

class Scheduler {
public:
	// constructor
	Scheduler();

	// calls client->schedulerCallback at the end of each period
	int every(SchedulerClient* client, unsigned long period);
	// calls client->schedulerCallback at most repeatCount times
	int every(SchedulerClient* client, unsigned long period,\
			int repeatCount);

	// oscillate pin
	int oscillate(byte pin, unsigned long period, \
		  byte startValue);
	// oscillate repeatCount times
	int oscillate(byte pin, unsigned long period, 
		  byte startValue, int repeatCount);
	
	// stop execution of an event with id
	void stop(byte id);
	// call in loop
	void update(void);

	// you can get a global instance
	static Scheduler* getInstance() {
		static Scheduler instance;
		return &instance;
	};

private:
	Event* events[SCH_MAX_EVENT];
	byte eventCnt;

	Event* getFreeEvent();
};

#endif
