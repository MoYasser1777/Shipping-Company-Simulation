#include "Truck.h"
int Truck:: counter = 0;
Truck::Truck(type t, int c, int ct, int s)
{
	counter++;
	numofjournies = 0;
	setTruckId(counter);
	setTruckType(t);
	setCapacity(c);
	setCheckUpTime(ct);
	setSpeed(s);
}
void Truck:: setTruckType(type t)
{
	Trucktype = t;
}
void Truck::setCapacity(int tc)
{
	capacity = tc;
}
void Truck::setCheckUpTime(int ct)
{
	CheckupTime = ct;
}
void Truck::setSpeed(int s)
{
	speed = s;
}
void Truck::setDeliveryInterval()
{
	int DI =  ceil(2 *((float)maxdistance / speed)) + sumloadtime;
	
	DeliveryInterval=DI;
}
void Truck::setTruckId(int id)
{
	TruckId = id;
}
void Truck::setsumloadtime(int lt)
{
	sumloadtime = lt;
}
void Truck::setmaxdistance(int md)
{
	maxdistance = md;
}
void Truck::setcargotype(type ct)
{
	cargotype = ct;
}
type Truck:: getTruckType() const
{
	return Trucktype;
}
int Truck::getTruckCapacity() const
{
	return capacity;
}
int Truck::getCheckUpTime() const
{
	return CheckupTime;
}
int Truck::getSpeed() const
{
	return speed;
}
int Truck::getDeliveryInterval()const
{
	return DeliveryInterval;
}
int Truck::getTruckId()const
{
	return TruckId;
}

void Truck::incrementj()
{
	numofjournies++;
}
void Truck::setactivetime()
{
	activetime = ceil((float)maxdistance / speed) + 2*sumloadtime;
}
float Truck::getactivetime()
{
	return activetime;
}

bool Truck::havecargos()
{
	
	return(!movingcargos.isEmpty()) ;
}

void Truck::movecargosfromloadingtomoving(const Time& currentTime)
{
	Cargo* pCargo;
    setDeliveryInterval();
	setFinishTime();
	for (int i = 0; i < capacity; i++)
	{
		loadingcargos.dequeue(pCargo);
		pCargo->setTID(TruckId);
		pCargo->setmovetime(currentTime);
		pCargo->setwaitingtime();
		pCargo->setdeliverytime(speed);
		int p = pCargo->getdeliverytime().timetohours();
		movingcargos.enqueue(pCargo,p);
		
	}

}

Cargo* Truck::delivercargo(const Time& currenttime)
{
  Cargo*pCargo;
  if (movingcargos.peek(pCargo) && pCargo->getdeliverytime() == currenttime)
  {
	  movingcargos.dequeue(pCargo);
	  return pCargo;

  }
  else
	  return NULL;
  

}

int Truck::getnumofjournies()
{
	return numofjournies;
}

void Truck::setMoveTime(Time MT)
{
	MoveTime = MT;
}

Time Truck::getMoveTime()
{
	return MoveTime;
}

void Truck::setFinishTime()
{
	FinishTime = MoveTime + DeliveryInterval;
}

Time Truck::getFinishTime()
{
	return FinishTime;
}

void Truck::setAvailTime()
{
	AvailTime = FinishTime + CheckupTime;
}

Time Truck::getAvailTime()
{
	return AvailTime;
}

type Truck::getcargotype()
{
	return cargotype ;
}

int Truck::getsumloadtime()
{
	return sumloadtime;
}

int Truck::getmaxdistance()
{
	return maxdistance;
}

int Truck::getcapacity()
{
	return capacity;
}

void Truck::addtoloadinglist(Cargo* pCargo)
{
	loadingcargos.enqueue(pCargo);
}

perQueue<Cargo*>& Truck::getmovingcargos()
{
	return movingcargos;
}

Queue<Cargo*>& Truck::getloadingcargos()
{
	return loadingcargos;
}

