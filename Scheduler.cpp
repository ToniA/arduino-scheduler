
#include "Scheduler.h"

Scheduler::Scheduler() {
	for(byte i=0; i<SCH_MAX_EVENT; i++) {
		this->events[i]=NULL;
	}
	this->eventCnt=0;
}

void Scheduler::update(void) {
	for(byte i=0; i<this->eventCnt; i++) {
		this->events[i]->update();
	}
}

void Scheduler::stop(byte id) {
	if(id>=this->eventCnt)
		return;
	this->events[id]->stop();
}

Event* Scheduler::getFreeEvent() {
	byte i;
	for(i=0; i<this->eventCnt; i++) {
		if(this->events[i]->getEventType()==Event::NONE)
			return this->events[i];
	}
	if(i>=SCH_MAX_EVENT) {
		return NULL;
	}
	Event *e=new Event(this->eventCnt++);
	this->events[i]=e;
	return e;
}

int Scheduler::oscillate(byte pin, unsigned long period, 
		  byte startValue, int repeatCount) {
	Event *e = this->getFreeEvent();
	if(e==NULL) {
		// Serial.println("getFreeEvent failed");
		return -1;
	}
	return e->oscillate(pin, period, startValue, repeatCount);
}

int Scheduler::oscillate(byte pin, unsigned long period, \
		  byte startValue) {
	return this->oscillate(pin, period, startValue, -1);
}

int Scheduler::every(SchedulerClient* client, unsigned long period,\
			int repeatCount) {
	Event *e = this->getFreeEvent();
	if(e==NULL)
		return -1;
	return e->every(client, period, repeatCount);
}

int Scheduler::every(SchedulerClient* client, unsigned long period) {
	return this->every(client, period, -1);
}
