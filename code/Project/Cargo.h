#pragma once
#include"Time.h"
#include"types.h"

class Cargo
{
	Time readytime;
	int loadtime;
	type cargotype;
	int distance;
	int cost;
	Time movetime;
	Time waitingtime;
	Time deliverytime;
	int CID;
	int TID;

public:
	Cargo();
	Cargo(type ct, Time rt, int id, int d, int lt, int c);
	void setreadytime(Time rt);
	void setloadtime(int lt);
	void setcargotype(type ct);
	void setdistance(int d);
	void setcost(int c);
	void setmovetime(Time mt);
	void setwaitingtime();
	void setdeliverytime(int speed);
	void setCID(int id);
	void setTID(int id);
	Time getreadytime()const;
	int getloadtime()const;
	type getcargotype()const;
	int getdistance()const;
	int getcost()const;
	Time getmovetime()const;
	Time getwaitingtime()const;
	Time getdeliverytime()const;
	int getCID()const;
	int getTID()const;
	int getpriority()const;//this is for vip cargos which have priority equation





};

