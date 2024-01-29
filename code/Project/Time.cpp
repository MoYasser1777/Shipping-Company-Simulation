#include "Time.h"

Time::Time()
{
}

Time::Time(int d, int h)
{
	setday(d);
	sethour(h);
}

void Time::settime(int d, int h)
{
	setday(d);
	sethour(h);
}

void Time::setday(int d)
{
	day = d;
}

void Time::sethour(int h)
{
	if (h <= 24 && h >= 0)
		hour = h;
	else
		hour = 0;
}

int Time::getday() const
{
	return day;
}

int Time::gethour() const
{
	return hour;
}

int Time::timetohours()
{
	return day*24+hour;
}

Time Time::operator-(Time t)
{
	int d, h;
	if (hour < t.hour)
	{
		h = 24 + hour - t.hour;
		d = day - 1 - t.day;
	}
	else
	{
		h = hour - t.hour;
		d = day - t.day;
	}
	return Time(d, h);
}

Time Time::operator+(Time t)
{   
	int d;
	int h;
	if (hour + t.hour >= 24)
	{
		h = hour + t.hour - 24;
		d = day + t.day + 1;

	}
	else
	{
		h = hour + t.hour ;
		d = day + t.day ;
	}

	return Time(d,h);
}

Time Time::operator+(int H)
{
	int h1, d1,h,d;
	h1 = H % 24;
	d1 = H / 24;
	if (h1 +hour >= 24)
	{
		h = hour + h1 - 24;
		d = day+d1 + 1;
	}
	else
	{
		h = hour + h1;
		d = day+d1;
	}
	return Time(d,h);
}
Time Time::operator-(int H)
{
	int h1, d1, h, d;
	h1 = H % 24;
	d1 = H / 24;
	if (hour - h1 < 0)
	{
		h = hour - h1 + 24;
		d = day - d1 - 1;
	}
	else
	{
		h = hour - h1;
		d = day - d1;
	}
	return Time(d, h);
}

bool Time::operator==(Time t)
{
	return (day==t.day&&hour==t.hour);
}

void Time::operator++(int i)
{
	if (hour <23)
	{
		hour++;
	}
	else
	{
		hour = 0;
		day++;
	}
}
