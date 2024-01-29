#include "Company.h"
#include <fstream>
#include "Event.h"
Company::Company()
{
	pUI = new UI;
	viploadingtruck = NULL;
	specialloadingtruck = NULL;
	normalloadingtruck = NULL;
	movingcargosnum = 0;
	totaltrucksactivetime = 0;
}

void Company::Load(string FileName)
{
	int day, hour, CargoID, CargoDistance, LoadTime, CargoCost;
	char eventtype, cargotype, c;
	ifstream LoadFile(FileName);
	LoadFile >> Nnum >> Snum >> VIPnum;
	LoadFile >> Nspeed >> Sspeed >> VIPspeed;
	LoadFile >> Ncapacity >> Scapacity >> VIPcapacity;
	LoadFile >> journeys;
	LoadFile >> Ncheckduration >> Scheckduration >> VIPcheckduration;
	LoadFile >> numofEvents;
	for (int i = 0; i < numofEvents; i++)
	{
		LoadFile >> eventtype;  //only one event R
		LoadFile >> cargotype;
		setCargoType(cargotype);
		LoadFile >> day >> c >> hour >> CargoID >> CargoDistance >> LoadTime >> CargoCost;
		Time eventtime(day, hour);
		createevent(getCargoType(), eventtime, CargoID, CargoDistance, LoadTime, CargoCost);
		
	}
	createtrucks();
}
void Company::Save(string FileName)
{
	ofstream SaveFile(FileName);
	SaveFile << "CDT" << "  " << "ID" << "  " << "PT" << "  " << "WT" << "  " << "TID"<< endl;
	int c = deliverdcargolist.getCount();
	Time totalwaitingtime(0, 0);
	for (int i = 0; i <c; i++)
	{
		Cargo* pCargo;
		deliverdcargolist.dequeue(pCargo);

		SaveFile << pCargo->getdeliverytime().getday() << ":" << pCargo->getdeliverytime().gethour() << "  " << pCargo->getCID() << "  " << pCargo->getreadytime().getday() << ":" << pCargo->getreadytime().gethour() << "  " << pCargo->getwaitingtime().getday() << ":" << pCargo->getwaitingtime().gethour() << "  " <<pCargo->getTID()<< endl;
		totalwaitingtime = totalwaitingtime + pCargo->getwaitingtime();
	}
	Time t = calcAverageWaitingTime(totalwaitingtime, c);

	SaveFile << "Cargos: " << gettotalcargos() << "[N: " << getnormalcargos() << ", S: " << getspecialcargos() << ", V: " << getVIPcargos() << "]" << endl;
	SaveFile << "Cargo Avg Wait = " << t.getday() << ":" << t.gethour() << endl;

	SaveFile << "Trucks: " << gettotaltrucks() << "[N: " << Nnum << ", S: " << Snum << ", V: " << VIPnum << "]" << endl;
	SaveFile << "Avg Active Time = " << int(averageactivetime*100) <<"%" << endl;
	SaveFile << "Avg Utilization = " << int(Truckutilization*100) <<"%" << endl;
}

void Company::createtrucks()
{
	for (int i = 0; i < Nnum; i++)
	{
		Truck* newtruck = new Truck(normal, Ncapacity, Ncheckduration, Nspeed);
		normaltrucklist.enqueue(newtruck);
	}
	for (int i = 0; i < Snum; i++)
	{
		Truck* newtruck = new Truck(special, Scapacity, Scheckduration, Sspeed);
		specialtrucklist.enqueue(newtruck);
	}
	for (int i = 0; i < VIPnum; i++)
	{
		Truck* newtruck = new Truck(VIP, VIPcapacity, VIPcheckduration, VIPspeed);
		VIPtrucklist.enqueue(newtruck);
	}

}

void Company::createevent(type cargotype, Time eventtime, int CargoID, int CargoDistance, int LoadTime, int CargoCost)
{
	Event* newEvent = new Event(cargotype, eventtime, CargoID, CargoDistance, LoadTime, CargoCost);
	Eventlist.enqueue(newEvent);
}

void Company::checkEventlist(const Time& currentTime)
{
	Event* pEvent;
	
		while( Eventlist.peek(pEvent)&& pEvent->geteventtime() == currentTime)
		{
			Eventlist.dequeue(pEvent);
			pEvent->Execute(this);
		}
	


}
void Company::addtocargolist(Cargo* pCargo)
{
	type ctype = pCargo->getcargotype();
	if (ctype == VIP)

	{
		int priority = pCargo->getpriority();
		VIPcargolist.enqueue(pCargo, priority);
	}

	else if (ctype == normal)
	{
		normalcargolist.enqueue(pCargo);
	}
	else if (ctype == special)
	{
		specialcargolist.enqueue(pCargo);
	}
}


void Company::update(const Time& currentTime)
{
	
	checkEventlist(currentTime);
	movefromloadingtomoving(currentTime);
	movecargostodeliverd(currentTime);
	movefrommovingtrucks(currentTime);
	movefromchecktoavail(currentTime);
	assigntoavailabetruck(currentTime);

}
Time Company::calcAverageWaitingTime(Time totTime, int n)
{
	int totalhours = totTime.timetohours();
	int averagehours = totalhours / n;
	int day = 0;
	while (averagehours >= 24)
	{
		averagehours -= 24;
		day += 1;
	}
	return Time(day, averagehours);
}
void Company::calcTruckStatistics(Time currenttime)
{
	int n = getnumofemptytrucks() + getnumofmoving() + getnumofloading();
	int totalsimtime = currenttime.timetohours();
	averageactivetime = (totaltrucksactivetime / n) / totalsimtime;
	Truckutilization = averageactivetime;
	
}

bool Company::offhours(Time current)
{
	if (current.gethour() > 23 || current.gethour() < 5)
		return true;
	return false;
}

void Company::assigntoavailabetruck(Time currenttime)
{
	if (offhours(currenttime))
		return;
	else
	{
		assignvipcargos(currenttime);
		assignspecialcargos(currenttime);
		assignnormalcargos(currenttime);
		
	}
}
void Company::assignvipcargos( Time currenttime)
{
	
	if (viploadingtruck)
		return;
	Cargo* pCargo;
	if (!VIPtrucklist.isEmpty())
	{
		if (VIPcargolist.getCount() < VIPcapacity)
			return;
		VIPtrucklist.dequeue(viploadingtruck);
		int loadtime = 0;
		Time movetime;
		int maxdist = 0;
		for (int i = 0; i < VIPcapacity; i++)
		{
			VIPcargolist.dequeue(pCargo);
			loadtime += pCargo->getloadtime();
			if (pCargo->getdistance() > maxdist) maxdist = pCargo->getdistance();
			//get loading list and enqueue to it
			viploadingtruck->addtoloadinglist(pCargo);
		}
		viploadingtruck->setmaxdistance(maxdist);
		viploadingtruck->setsumloadtime(loadtime);
       
		if (loadtime > (23 - currenttime.gethour()))
         movetime = currenttime + loadtime+5;
		else 
		movetime = currenttime + loadtime ;
	
		viploadingtruck->setMoveTime(movetime);
		viploadingtruck->setcargotype(VIP);
		return;

	}
	else if (!normaltrucklist.isEmpty())
	{       
			if (VIPcargolist.getCount() < Ncapacity)
				return;
			normaltrucklist.dequeue(viploadingtruck);
		    int maxdist = 0;
		    int loadtime = 0;
		    Time movetime;
			for (int i = 0; i < Ncapacity; i++)
			{
				VIPcargolist.dequeue(pCargo);
				loadtime += pCargo->getloadtime();
				if (pCargo->getdistance() > maxdist) maxdist = pCargo->getdistance();
				//get loading list and enqueue to it
				viploadingtruck->addtoloadinglist(pCargo);
			}
			
			viploadingtruck->setmaxdistance(maxdist);
		    viploadingtruck->setsumloadtime(loadtime);
			if (loadtime > (23 - currenttime.gethour()))
				movetime = currenttime + loadtime + 5;
			else
				movetime = currenttime + loadtime;
			viploadingtruck->setMoveTime(movetime);
			viploadingtruck->setcargotype(VIP);
			return;	
	}
	else if (!specialtrucklist.isEmpty())
	{
		if (VIPcargolist.getCount() < Scapacity)
			return ;
		specialtrucklist.dequeue(viploadingtruck);
		        int maxdist = 0;
               	int loadtime = 0;
	            Time movetime;
				for (int i = 0; i < Scapacity; i++)
				{
					VIPcargolist.dequeue(pCargo);
					loadtime += pCargo->getloadtime();
					if (pCargo->getdistance() > maxdist) maxdist = pCargo->getdistance() ;
					//get loading list and enqueue to it
					viploadingtruck->addtoloadinglist(pCargo);
				}
				if (loadtime > (23 - currenttime.gethour()))
					movetime = currenttime + loadtime + 5;
				else
					movetime = currenttime + loadtime;
				viploadingtruck->setMoveTime(movetime);
				viploadingtruck->setmaxdistance(maxdist);
		        viploadingtruck->setsumloadtime(loadtime);
				viploadingtruck->setcargotype(VIP);	
	}
}
void Company::assignspecialcargos(Time currenttime)
{

	Cargo* pCargo;
	if (!specialloadingtruck&&specialcargolist.getCount() >= Scapacity&&specialtrucklist.dequeue(specialloadingtruck))
	{
		
		
		        int maxdist = 0;
	           	int loadtime = 0;
	        	Time movetime;
				for (int i = 0; i < Scapacity; i++)
				{
					specialcargolist.dequeue(pCargo);
					loadtime += pCargo->getloadtime();
                    if (pCargo->getdistance() > maxdist) maxdist = pCargo->getdistance();
					//get loading list and enqueue to it
					specialloadingtruck->addtoloadinglist(pCargo);
				}
				if (loadtime > (23 - currenttime.gethour()))
					movetime = currenttime + loadtime + 5;
				else
					movetime = currenttime + loadtime;
				specialloadingtruck->setMoveTime(movetime);
				specialloadingtruck->setmaxdistance(maxdist);
		        specialloadingtruck->setsumloadtime(loadtime);
				specialloadingtruck->setcargotype(special);
			
	}
}
void Company::assignnormalcargos(Time currenttime)
{
	if (normalloadingtruck)
		return;
	Cargo* pCargo;
	if (!normaltrucklist.isEmpty())

	{
		if (normalcargolist.getCount() < Ncapacity)
			return;
		normaltrucklist.dequeue(normalloadingtruck);
		int maxdist = 0;
		int loadtime = 0;
		Time movetime;
		for (int i = 0; i < Ncapacity; i++)
		{
			normalcargolist.dequeue(pCargo);
			loadtime += pCargo->getloadtime();
			if (pCargo->getdistance() > maxdist) maxdist = pCargo->getdistance() ;
			//get loading list and enqueue to it
			normalloadingtruck->addtoloadinglist(pCargo);
		}
		if (loadtime > (23 - currenttime.gethour()))
			movetime = currenttime + loadtime + 5;
		else
			movetime = currenttime + loadtime;
		normalloadingtruck->setMoveTime(movetime);
		normalloadingtruck->setmaxdistance(maxdist);
		normalloadingtruck->setsumloadtime(loadtime);
		normalloadingtruck->setcargotype(normal);
		return;

	}
	else if (!VIPtrucklist.isEmpty())
	{
		if (normalcargolist.getCount() < VIPcapacity)
			return;
		    VIPtrucklist.dequeue(normalloadingtruck);
		    int maxdist = 0;
		    int loadtime = 0;
		    Time movetime;
			for (int i = 0; i < VIPcapacity; i++)
			{
				normalcargolist.dequeue(pCargo);
				loadtime += pCargo->getloadtime();
				if (pCargo->getdistance() > maxdist) maxdist = pCargo->getdistance() ;
				//get loading list and enqueue to it
				normalloadingtruck->addtoloadinglist(pCargo);
			}
			if (loadtime > (23 - currenttime.gethour()))
				movetime = currenttime + loadtime + 5;
			else
				movetime = currenttime + loadtime;
			normalloadingtruck->setMoveTime(movetime);
            normalloadingtruck->setmaxdistance(maxdist);
		    normalloadingtruck->setsumloadtime(loadtime);
			normalloadingtruck->setcargotype(normal);
		
	}
}
void Company::movefromloadingtomoving(const Time& currentTime)
{
	if (offhours(currentTime))
		return;
	if (viploadingtruck&& viploadingtruck->getMoveTime()== currentTime)
	{
		viploadingtruck->movecargosfromloadingtomoving(currentTime);
		movingcargosnum += viploadingtruck->getcapacity();
		int p = viploadingtruck->getFinishTime().timetohours();
		movingtrucklist.enqueue(viploadingtruck,p);
		viploadingtruck = NULL;

	}
	if (normalloadingtruck && normalloadingtruck->getMoveTime() == currentTime)
	{
		normalloadingtruck->movecargosfromloadingtomoving(currentTime);
		movingcargosnum += normalloadingtruck->getcapacity();
		int p = normalloadingtruck->getFinishTime().timetohours();
		movingtrucklist.enqueue(normalloadingtruck, p);
		normalloadingtruck = NULL;
	}
	if (specialloadingtruck && specialloadingtruck->getMoveTime() == currentTime)
	{
		specialloadingtruck->movecargosfromloadingtomoving(currentTime);
		movingcargosnum += specialloadingtruck->getcapacity();
		int p = specialloadingtruck->getFinishTime().timetohours();
		movingtrucklist.enqueue(specialloadingtruck, p);
	    specialloadingtruck = NULL;
	}

}
void Company::movecargostodeliverd(const Time& currentTime)
{
		Queue<Truck*> temp;
		Truck* pTruck;
		Cargo* pCargo;
		bool stop;
		while (!movingtrucklist.isEmpty())
		{
			stop = false;
			movingtrucklist.dequeue(pTruck);
			temp.enqueue(pTruck);
			while (!stop)
			{
				pCargo = pTruck->delivercargo(currentTime);
				if (pCargo)
				{
					if (pCargo->getcargotype() == normal)
						normaldeliverdcargolist.enqueue(pCargo);
					else if (pCargo->getcargotype() == special)
						specialdeliverdcargolist.enqueue(pCargo);
					else if (pCargo->getcargotype() == VIP)
						VIPdeliverdcargolist.enqueue(pCargo);
					movingcargosnum--;
					deliverdcargolist.enqueue(pCargo);

				}
				else
					stop = true;

			}
			

		}
		int p;
		while (!temp.isEmpty())
		{
			temp.dequeue(pTruck);
			p = pTruck->getFinishTime().timetohours();
			movingtrucklist.enqueue(pTruck, p);
		}
}
void Company::movefrommovingtrucks(const Time& currentTime)
{
	Truck* pTruck;

	while (movingtrucklist.peek(pTruck)&&pTruck->getFinishTime()==currentTime)
	{
		
			movingtrucklist.dequeue(pTruck);
			pTruck->setactivetime();
			totaltrucksactivetime += pTruck->getactivetime();
			pTruck->incrementj();
			if (pTruck->getnumofjournies() % journeys==0)
			{
				pTruck->setAvailTime();
				if (pTruck->getTruckType() == VIP)
					VIPchecktrucklist.enqueue(pTruck);
				else if (pTruck->getTruckType() == normal)
					normalchecktrucklist.enqueue(pTruck);
				else if (pTruck->getTruckType() == special)
					specialchecktrucklist.enqueue(pTruck);
			}
			else
			{
				if (pTruck->getTruckType() == VIP)
					VIPtrucklist.enqueue(pTruck);
				else if (pTruck->getTruckType() == normal)
					normaltrucklist.enqueue(pTruck);
				else if (pTruck->getTruckType() == special)
					specialtrucklist.enqueue(pTruck);
			}

	

	}
}
void Company::movefromchecktoavail(const Time& currentTime)
{
	Truck* pTruck;
	while (VIPchecktrucklist.peek(pTruck)&& pTruck->getAvailTime() == currentTime)
	{
		
			VIPchecktrucklist.dequeue(pTruck);
			VIPtrucklist.enqueue(pTruck);
		

	}
	while (normalchecktrucklist.peek(pTruck)&& pTruck->getAvailTime() == currentTime)
	{
		
			normalchecktrucklist.dequeue(pTruck);
			normaltrucklist.enqueue(pTruck);
		

	}
	if (specialchecktrucklist.peek(pTruck)&& pTruck->getAvailTime() == currentTime)
	{
		
			specialchecktrucklist.dequeue(pTruck);
			specialtrucklist.enqueue(pTruck);
		

	}


}
Truck* Company::getviploadingtruck()
{
	return viploadingtruck;
}
Truck* Company::getspecialloadingtruck()
{
	return specialloadingtruck;
}
Truck* Company::getnormalloadingtruck()
{
	return normalloadingtruck;
}
bool Company::Endsimulation(Time currenttime)
{
	if (Eventlist.isEmpty() && getnumofdeliverd() == numofEvents&& getnumofemptytrucks()==gettotaltrucks())
	{
		calcTruckStatistics(currenttime);
		return true;
	}
	return false;
}
int Company::getnumofwaiting()const
{
	return (VIPcargolist.getCount() + normalcargolist.getCount() + specialcargolist.getCount());
}
int Company::getnumofdeliverd()const
{
	return (VIPdeliverdcargolist.getCount()+normaldeliverdcargolist.getCount()+specialdeliverdcargolist.getCount());
}
int Company::getnumofloading()const
{
	int num = 0;
	if (viploadingtruck)
		num++;
	if (normalloadingtruck)
		num++;
	if (specialloadingtruck)
		num++;
	return num;

}
int Company::getnumofmoving()const
{
	return movingtrucklist.getCount();
}
int Company::getnumofchecktrucks()const
{
	return normalchecktrucklist.getCount()+specialchecktrucklist.getCount()+VIPchecktrucklist.getCount();
}
int Company::getnumofemptytrucks()const
{
	return normaltrucklist.getCount()+specialtrucklist.getCount()+VIPtrucklist.getCount();
}
int Company::getnormalcargos() const
{
	return normaldeliverdcargolist.getCount();
}
int Company::getspecialcargos() const
{
	return specialdeliverdcargolist.getCount();
}
int Company::getVIPcargos() const
{
	return VIPdeliverdcargolist.getCount();
}
perQueue<Cargo*>& Company::getVIPcargolist() 
{
	return VIPcargolist;
}
Queue<Cargo*>& Company::getnormalcargolist()
{
	return normalcargolist;
}
Queue<Cargo*>& Company::getspecialcargolist()
{
	return specialcargolist;
}

Queue<Cargo*>& Company::getVIPdeliverdcargolist()
{
	return VIPdeliverdcargolist;
}
Queue<Cargo*>& Company::getnormaldeliverdcargolist()
{
	return normaldeliverdcargolist;
}
Queue<Cargo*>& Company::getspecialdeliverdcargolist()
{
	return specialdeliverdcargolist;
}

Queue<Truck*>& Company::getVIPtrucklist()
{
	return VIPtrucklist;
}

Queue<Truck*>& Company::getnormaltrucklist()
{
	return normaltrucklist;
}

Queue<Truck*>& Company::getspecialtrucklist()
{
	return specialtrucklist;
}



perQueue<Truck*>& Company::getmovingtrucklist()
{
	return movingtrucklist;
}

Queue<Truck*>& Company::getVIPchecktrucklist()
{
	return VIPchecktrucklist;
}

Queue<Truck*>& Company::getnormalchecktrucklist()
{
	return normalchecktrucklist;
}

Queue<Truck*>& Company::getspecialchecktrucklist()
{
	return specialchecktrucklist;
}



void Company::setCargoType(char c)
{
	if (c == 'N')
		Cargotype = normal;
	else if (c == 'S')
		Cargotype = special;
	else if (c == 'V')
		Cargotype = VIP;
}
type Company::getCargoType()const
{
	return Cargotype;
}

UI* Company::getUI()const
{
	return pUI;
}
int Company::gettotalcargos()const
{
	return normaldeliverdcargolist.getCount()+specialdeliverdcargolist.getCount()+VIPdeliverdcargolist.getCount();
}

int Company::gettotaltrucks() const
{
	return Nnum+Snum+VIPnum;
}

int Company::getmovingcargosnum() const
{
	return movingcargosnum;
}





