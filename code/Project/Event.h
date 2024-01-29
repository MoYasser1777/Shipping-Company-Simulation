#pragma once
#include"Time.h"
#include"types.h"
#include"Cargo.h"
#include"Company.h"
class Company;
class Event
{
	type cargotype;
	Time eventtime;
	int CID;
	int distance;
	int loadtime;
	int cost;
public:
	Event();
	Event(type ct, Time et, int id, int d, int lt, int c);
	void setcargotype(type ct);
	void seteventtime(Time et);
	void setCID(int id);
	void setdistance(int d);
	void setloadtime(int lt);
	void setcost(int c);
	Time geteventtime()const;
	void Execute(Company*pCompany);//creates a cargo and call the function which adds it to waiting cargo lists

};

