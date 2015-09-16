/*
 * by Ozan Oner
 * base class for clients
 */

#ifndef SCHEDULER_CLIENT_H
#define SCHEDULER_CLIENT_H

class SchedulerClient {
public:
	SchedulerClient(void (*cb)(int)) { this->cb=cb; };
	SchedulerClient() { this->cb=NULL; }

	virtual void schedulerCallback(int eventId) {
		if(this->cb!=NULL)
			this->cb(eventId);
	};
	virtual void schedulerEnded(int evendId) { };
protected:
	void (*cb)(int);
};

#endif
