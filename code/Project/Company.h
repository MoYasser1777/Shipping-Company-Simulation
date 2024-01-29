#pragma once
#include <iostream>
#include <fstream>
#include "types.h"
#include "Cargo.h"
#include "Truck.h"
#include"Queue.h"
#include "Event.h"
#include"Queue.h"
#include"perQueue.h"
#include"UI.h"

class Event;
class UI;

using namespace std;
class Company
{
private:
	type Cargotype;
	int Truckscount,
		Nnum, Snum, VIPnum,//number of trucks of each type
		Nspeed, Sspeed, VIPspeed,
		Ncapacity, Scapacity, VIPcapacity,
		journeys, numofEvents,
		movingcargosnum,
		Ncheckduration, Scheckduration, VIPcheckduration;
	float  averageactivetime, Truckutilization, totaltrucksactivetime;
	UI* pUI;
	// lists of trucks and cargos
	Queue<Event*> Eventlist;
	perQueue<Cargo*> VIPcargolist;//perqueue depends on weighted equation
	Queue<Cargo*> normalcargolist;
	Queue<Cargo*> specialcargolist;
	Queue<Cargo*> VIPdeliverdcargolist;
	Queue<Cargo*> normaldeliverdcargolist;
	Queue<Cargo*> specialdeliverdcargolist;
	Queue<Cargo*> deliverdcargolist;
	Queue<Truck*> VIPtrucklist;
	Queue<Truck*> normaltrucklist;
	Queue<Truck*> specialtrucklist;
	perQueue<Truck*> movingtrucklist;//perqueue depends on delivery time(truck which deliver first will be out of queue first)
	Queue<Truck*> VIPchecktrucklist;
	Queue<Truck*> normalchecktrucklist;
	Queue<Truck*> specialchecktrucklist;
	Truck* viploadingtruck, * specialloadingtruck, * normalloadingtruck; //Three loading trucks only , one truck from each type





public:
	Company();
	void setCargoType(char c);
	void Load(string FileName);
	void Save(string FileName);
	void createtrucks();
	void createevent(type cargotype, Time eventtime, int CargoID, int CargoDistance, int LoadTime, int CargoCost);
	void checkEventlist(const Time& currentTime);//checks if there is an event in the current tme and excute it
	void addtocargolist(Cargo* pCargo);//adds a ready cargo to the waiting lists (different types list)
	void update(const Time& currentTime);//calls  functions that edit in all company lists
	bool Endsimulation(Time currenttime);//checks if all cargos are deliverd
	Time calcAverageWaitingTime(Time totTime, int n); // average wait time from all cargos waiting
	void calcTruckStatistics(Time currenttime);
	bool offhours(Time current); //return true is there is off hours to stop loading any cargos at these hours
	void assigntoavailabetruck(Time currentTime); // calls assign to vip,normal and special
	void assignvipcargos( Time currentTime);
	void assignspecialcargos(Time currentTime);
	void assignnormalcargos(Time currentTime) ;
	void movefromloadingtomoving(const Time& currentTime);
	void movecargostodeliverd(const Time& currentTime); // move cargos from moving list inside truck to deliverd list(s)
	void movefrommovingtrucks(const Time& currentTime);
	void movefromchecktoavail(const Time& currentTime);
	type getCargoType()const; 
	int getnumofwaiting()const; // get num of waiting cargos
	int getnumofdeliverd()const; //get num of deliverd cargos
	int getnumofloading()const; //get num of loading cargos
	int getnumofmoving()const;  //get num of moving cargos
	int getnumofchecktrucks()const; // get num of trucks in check up 
	int getnumofemptytrucks()const; //get num of available (empty)trucks
	int getnormalcargos()const; //get num of normal cargos
	int getspecialcargos()const; //get num of special cargos
	int getVIPcargos()const; //get num of vip cargos
	int gettotalcargos()const; //get num of total cargos
	int gettotaltrucks()const; //get num of total trucks
	int getmovingcargosnum()const; //get sum of moving cargos
	//getters of the lists to be printed in ui class
	perQueue<Cargo*>& getVIPcargolist();
	Queue<Cargo*>& getnormalcargolist();
	Queue<Cargo*>& getspecialcargolist();
	Queue<Cargo*>&getVIPdeliverdcargolist();
	Queue<Cargo*>& getnormaldeliverdcargolist();
	Queue<Cargo*>& getspecialdeliverdcargolist();
	Queue<Truck*>& getVIPtrucklist();
	Queue<Truck*>& getnormaltrucklist();
	Queue<Truck*>& getspecialtrucklist();
	perQueue<Truck*>& getmovingtrucklist();
	Queue<Truck*>& getVIPchecktrucklist();
	Queue<Truck*>& getnormalchecktrucklist();
	Queue<Truck*>& getspecialchecktrucklist();
	Truck* getviploadingtruck();
	Truck* getspecialloadingtruck();
	Truck* getnormalloadingtruck();
	UI* getUI()const; //get pointer to ui class
	
	
	
};

