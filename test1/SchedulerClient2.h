

#include <SchedulerClient.h>

class SchedulerClient2: public SchedulerClient {
public:
	void schedulerCallback(int eventId) {
		Serial.print("Callback from event(SchedulerClient2): ");
		Serial.println(eventId);
	};
	void schedulerEnded(int eventId) {
		Serial.print("Event end(SchedulerClient2): ");
		Serial.println(eventId);
	};
};
