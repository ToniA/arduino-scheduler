See http://www.codeproject.com/Tips/731031/Scheduler-Library-for-Arduino

Enhancements
* Header files no longer produce code
* The number of scheduled events is dynamic, just give the number of events as a parameter to the constructor like this:

```
Scheduler scheduler(15);
```

or

```
Scheduler *scheduler;
scheduler = new Scheduler(numberOfEvents);
```
