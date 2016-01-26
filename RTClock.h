// RTClock.h

#ifndef _RTCLOCK_h
#define _RTCLOCK_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

// RTC Header Files
#include <Wire.h>
#include <ds3231.h>
#include <config.h>

#define UNIT_HOUR 0
#define UNIT_MINUTE 1
#define UNIT_SECOND 2
#define UNIT_DAY 3
#define UNIT_MONTH 4
#define UNIT_YEAR 5
#define UNIT_YEAR_SHORT 6

class RTClockClass
{
public:
	RTClockClass();
	~RTClockClass();
	void resetClock();
	void incrementUnit(int);
	int getUnit(int);

private:
	struct ts t; // RTC time structure
};

#endif

