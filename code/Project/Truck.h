#pragma once
#include "types.h"
#include "perQueue.h"
#include "Cargo.h"
#include "Queue.h"
#include "Time.h"
class Truck
{
	type Trucktype;
	type cargotype;
	int capacity;
	int CheckupTime;   //in hours
	int speed;
	int sumloadtime;
	int maxdistance;
	Time MoveTime;
	int DeliveryInterval;
	Time FinishTime;
	Time AvailTime;
	int numofjournies;
	int TruckId;
	float activetime;
	int cargosdeliverd;
	static int counter;// to set the truck id
	//lists contains the cargos assigned to the truck
	perQueue<Cargo*> movingcargos;
	Queue<Cargo*> loadingcargos;


public:
	Truck(type t, int c, int ct, int s);
	void setTruckType(type t);
	void setCapacity(int tc);
	void setCheckUpTime(int ct);
	void setSpeed(int s);
	void setDeliveryInterval();
	void setTruckId(int id);
	void setsumloadtime(int lt); //sumloadtime of all cargos on truck
	void setmaxdistance(int md); //max distance from cargos distances to set the truck's distance
	void setcargotype(type ct);
	type getTruckType() const; //get thr type of cargos on the truck
	int getTruckCapacity() const;
	int getCheckUpTime() const;
	int getSpeed()const;
	int getDeliveryInterval()const;
	int getTruckId()const;
	void incrementj();
	void setactivetime();
	float getactivetime();
	bool havecargos();
	void movecargosfromloadingtomoving(const Time &currenttime); 
	Cargo* delivercargo(const Time& currenttime); //move cargos from moving list of this truck to deliverd list(s)
	int getnumofjournies(); //num of journeeys before the checkup
	void setMoveTime(Time MT);
	Time getMoveTime();
	void setFinishTime();
	Time getFinishTime();
	void setAvailTime();
	Time getAvailTime();
	type getcargotype();
	int getsumloadtime();
	int getmaxdistance();
	int getcapacity();
	void addtoloadinglist(Cargo* pCargo);

	//getters to lists of each truck
	perQueue<Cargo*>& getmovingcargos();
	Queue<Cargo*>& getloadingcargos();

	

};




