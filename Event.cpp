
#include "Event.h"

Event::Event(byte id)
{
	this->id=id;
	this->reset();
}

void Event::reset() {
	this->eventType = NONE;
	this->repeatCount=0;
	this->client=NULL;
}

void Event::update(void)
{
	unsigned long now = millis();
	if(now<this->next || this->eventType==NONE)
		return;
	
	switch(this->eventType) {
		case EVERY:
			this->client->schedulerCallback(this->id);
			break;
		case OSCILLATE:
			digitalWrite(this->pin, this->pinState);
			this->pinState = !this->pinState;
			break;
		default:
			break;
	}

	if(this->repeatCount<=-1) {
		// infinite repeat
		this->setNext(now);
	}
	else if(--this->repeatCount==0) {
		// done
		if(this->eventType==EVERY) {
			this->client->schedulerEnded(this->id);
		}
		this->reset();
	}
	else {
		this->setNext(now);
	}
}

void Event::setNext(unsigned long lastcall) {
	while(this->next<=lastcall) {
		this->next+=this->period;
	}
}

int Event::every(SchedulerClient* cl, unsigned long period, \
		int repeatCount) {
	if(this->eventType!=NONE)
		return -1;
	if(cl==NULL)
		return -2;
	if(repeatCount==0)
		return -3;
	this->eventType = EVERY;
	this->client=cl;

	this->repeatCount=repeatCount;
	this->period=period;
	this->next=millis()+this->period;
	return (int)this->id;
}

int Event::oscillate(byte pin, unsigned long period, \
		byte startValue, int repeatCount) {
	if(this->eventType!=NONE) {
		// Serial.println("this->eventType!=NONE");
		return -1;
	}
	if(repeatCount==0) {
		// Serial.println("repeatCount==0");
		return -3;
	}
	this->eventType=OSCILLATE;
	this->pin=pin;
	this->pinState=startValue;
	pinMode(this->pin, OUTPUT);

	this->repeatCount=repeatCount;
	this->period=period;
	this->next=millis()+this->period;
	return (int)this->id;
}
