#include "RTClock.h"

RTClockClass::RTClockClass()
{
}

RTClockClass::~RTClockClass()
{
}

void RTClockClass::resetClock()
{
	t.hour = 0;
	t.min = 0;
	t.sec = 0;
	t.mday = 1;
	t.mon = 1;
	t.year = 2016;
	t.year_s = 16;

	DS3231_set(t);

	return;
}


int RTClockClass::getUnit(int unit)
{
	DS3231_get(&t); // Get updated time

	switch (unit)
	{
	case UNIT_HOUR:
		return t.hour;
		break;
	case UNIT_MINUTE:
		return t.min;
		break;
	case UNIT_SECOND:
		return t.sec;
		break;
	case UNIT_DAY:
		return t.mday;
		break;
	case UNIT_MONTH:
		return t.mon;
		break;
	case UNIT_YEAR:
		return t.year;
		break;
	case UNIT_YEAR_SHORT:
		return t.year_s;
		break;
	}
}

void RTClockClass::incrementUnit(int unit)
{
	bool isLeap = false;
	
	switch (unit)
	{
	case UNIT_HOUR:
		if (++t.hour == 24)
			t.hour = 0;
		break;
	case UNIT_MINUTE:
		if (++t.min == 60)
			t.min = 0;
		t.sec = 0;
		break;
	case UNIT_SECOND:
		++t.sec;
		break;
	case UNIT_DAY:
		++t.mday;
		switch (t.mon) // See which month you're incrementing, adjust accordingly
		{
			case 1: if (t.mday == 32) t.mday = 1; break;
			case 2: // Leap year evil-ness
				if ((t.year % 4 == 0) && !(t.year % 100 == 0) || (t.year % 400 == 0))
					isLeap = true;
				if ((t.mday == 29) && !isLeap) // Normal Year
					t.mday = 1;
				else if (t.mday == 30) // Leap year
					t.mday = 1;
				break;
			case 3: if (t.mday == 32) t.mday = 1; break;
			case 4: if (t.mday == 31) t.mday = 1; break;
			case 5: if (t.mday == 32) t.mday = 1; break;
			case 6: if (t.mday == 31) t.mday = 1; break;
			case 7: if (t.mday == 32) t.mday = 1; break;
			case 8: if (t.mday == 32) t.mday = 1; break;
			case 9: if (t.mday == 31) t.mday = 1; break;
			case 10: if (t.mday == 32) t.mday = 1; break;
			case 11: if (t.mday == 31) t.mday = 1; break;
			case 12: if (t.mday == 32) t.mday = 1; break;
		}
		break;
	case UNIT_MONTH:
		if (++t.mon == 13)
			t.mon = 1;
		break;
	case UNIT_YEAR:
		++t.year;
		++t.year_s;
		break;
	}

	DS3231_set(t);
}