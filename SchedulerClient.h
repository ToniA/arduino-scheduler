/*
 * by Ozan Oner
 * base class for clients
 */

#ifndef SCHEDULER_CLIENT_H
#define SCHEDULER_CLIENT_H

#include "Arduino.h"

class SchedulerClient {
public:
    SchedulerClient(void (*cb)(int));
    SchedulerClient();

    virtual void schedulerCallback(int eventId);
    virtual void schedulerEnded(int evendId);
protected:
    void (*cb)(int);
};

#endif
