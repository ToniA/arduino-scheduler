#include "SchedulerClient.h"

SchedulerClient::SchedulerClient(void (*cb)(int))
{
   this->cb = cb;
};

SchedulerClient::SchedulerClient()
{
    this->cb = NULL;
}

void SchedulerClient::schedulerCallback(int eventId)
{
    if(this->cb != NULL)
        this->cb(eventId);
};

void SchedulerClient::schedulerEnded(int evendId)
{
};
