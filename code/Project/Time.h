#pragma once
class Time
{
	int day;
	int hour;
public:
	Time();
	Time(int d,int h);
	void settime(int d, int h);
	void setday(int d);
	void sethour(int h);
	int getday()const;
	int gethour()const;
	int timetohours(); // convert time format day:hour to --> int hours
	Time operator-(Time t); //time-time
	Time operator+(Time t); ///time+time
	Time operator+(int H); //time+integer
	Time operator-(int H); //Time-intger
	bool operator==(Time t);
	void operator++(int i);


};

