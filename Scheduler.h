
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

#define SCH_DEFAULT_EVENTS 10

class Scheduler {
public:
    // constructor
    Scheduler(byte numberOfEvents = SCH_DEFAULT_EVENTS);

    // dynamic allocation also requires a destructor
    ~Scheduler(void);

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
    static Scheduler* getInstance();

private:
    Event** events;
    byte eventCnt;
    byte maxEvents;

    Event* getFreeEvent();
};

#endif
