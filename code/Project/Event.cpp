#include "Event.h"

Event::Event()
{
}

Event::Event(type ct, Time et, int id, int d, int lt, int c)
{
	setcargotype( ct);
    seteventtime( et);
    setCID( id);
    setdistance( d);
    setloadtime( lt);
	setcost(c);

}

void Event::setcargotype(type ct)
{
	cargotype = ct;
}

void Event::seteventtime(Time et)
{
	eventtime = et;
}

void Event::setCID(int id)
{
	CID = id;
}

void Event::setdistance(int d)
{
	distance = d;
}

void Event::setloadtime(int lt)
{
	loadtime = lt;
}

void Event::setcost(int c)
{
	cost = c;
}

Time Event::geteventtime()const
{
	return eventtime;
}

void Event::Execute(Company* pCompany)
{
	Cargo* newcargo = new Cargo (cargotype, eventtime, CID, distance, loadtime, cost);
	pCompany->addtocargolist(newcargo);


}
