#include "Cargo.h"
#include"Time.h"
#include"types.h"
#include<iostream>
using namespace std;


Cargo::Cargo()
{
}

Cargo::Cargo(type ct, Time rt, int id, int d, int lt, int c)
{
	setcargotype(ct);
	setreadytime(rt);
	setCID(id);
	setdistance(d);
	setloadtime(lt);
	setcost(c);
}

void Cargo::setreadytime(Time rt)
{
	readytime = rt;
}

void Cargo::setloadtime(int lt)
{
	loadtime = lt;
}

void Cargo::setcargotype(type ct)
{
	cargotype = ct;
}

void Cargo::setdistance(int d)
{
	distance = d;
}

void Cargo::setcost(int c)
{
	cost = c;
}

void Cargo::setmovetime(Time mt)
{
	movetime = mt;
}

void Cargo::setwaitingtime()
{
	
	waitingtime = movetime-readytime; 
}

void Cargo::setdeliverytime(int speed)
{
	deliverytime =movetime+ceil(distance/speed)+loadtime ;  
}

void Cargo::setCID(int id)
{
	CID = id;

}

void Cargo::setTID(int id)
{
	TID = id;
}

Time Cargo::getreadytime()const
{
	return readytime;
}

int Cargo::getloadtime()const
{
	return loadtime;
}

type Cargo::getcargotype()const
{
	return cargotype;
}

int Cargo::getdistance()const
{
	return distance;
}

int Cargo::getcost()const
{
	return cost;
}

Time Cargo::getmovetime()const
{
	return movetime;
}

Time Cargo::getwaitingtime()const
{
	return waitingtime;
}

Time Cargo::getdeliverytime()const
{
	return deliverytime;
}

int Cargo::getCID()const
{
	return CID;
}

int Cargo::getTID()const
{
	return TID;
}

int Cargo::getpriority()const//priority equation which depends on readytime,cost,distance
{
	 
	int Time = readytime.getday() * 24 + readytime.gethour();
	int priority = ((distance * Time) / cost) * 10;
	return priority;
}
