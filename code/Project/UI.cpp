#include "UI.h"
ostream& operator<<(ostream& output, Queue<Cargo*>& queue)
{

	Node<Cargo*>* ptr;
	ptr = queue.getfront();
	while (ptr)
	{
		if (ptr ==queue.getfront())
			output << ptr->getItem()->getCID();
		else 
		output <<","<< ptr->getItem()->getCID() ;
		ptr = ptr->getNext();
	}
	
	return output;

}
ostream& operator<<(ostream& output, perQueue<Cargo*>& queue)
{

	Node<Cargo*>* ptr;
	ptr = queue.getfront();
	while (ptr)
	{
		if (ptr == queue.getfront())
		{
			output << ptr->getItem()->getCID();
		}
		else
			output << "," << ptr->getItem()->getCID();
		ptr = ptr->getNext();
	}
	
	return output;
}
ostream& operator<<(ostream& output, Queue<Truck*>& queue)
{

	Node<Truck*>* ptr;
	ptr = queue.getfront();
	while (ptr)
	{
		if (ptr == queue.getfront())
		{
			output << ptr->getItem()->getTruckId();
		}
		else
		output << "," << ptr->getItem()->getTruckId();
		ptr = ptr->getNext();
	}

	return output;

}
ostream& operator<<(ostream& output, perQueue<Truck*>& queue)
{

	Node<Truck*>* ptr;
	ptr = queue.getfront();
	while (ptr)
	{
		if (ptr->getItem()->havecargos())
		{
			output << ptr->getItem()->getTruckId();
			if (ptr->getItem()->getcargotype() == normal)
			{
				output << "[";
				output << ptr->getItem()->getmovingcargos();
				output << "] ";
			}
			else if (ptr->getItem()->getcargotype() == special)
			{
				output << "(";
				output << ptr->getItem()->getmovingcargos();
				output << ") ";
			}
			else if (ptr->getItem()->getcargotype() == VIP)
			{
				output << "{";
				output << ptr->getItem()->getmovingcargos();
				output << "} ";
			}
		}
		
		ptr = ptr->getNext();
	}

	return output;

}

UI::UI()
{
	
}

void UI::start(Company* pCompany)
{
	print("Enter the file name to load its data: ");
	string file = getstring() + ".txt";
	pCompany->Load(file);
	Setprogrammode();
}

void UI::simulate(Company* pCompany)
{
	Time currentTime(0, 0);
	if (programmode == Interactive)
	{
		while (!pCompany->Endsimulation(currentTime))
		{

			if (cin.get() == '\n')
			{
				pCompany->update(currentTime);
				PrintInfo(currentTime, pCompany);
				currentTime++;
			}
		}
		print("Simulation Ends");
	}
	else if (programmode == Stepbystep)
	{
		while (!pCompany->Endsimulation(currentTime))
		{

			Sleep(1000);
			pCompany->update(currentTime);
			PrintInfo(currentTime, pCompany);
			currentTime++;

		}
		print("Simulation Ends");

	}
	else if (programmode == Silent)
	{
		while (!pCompany->Endsimulation(currentTime))
		{

			pCompany->update(currentTime);
			currentTime++;

		}
		print("Silent Mode");
	    print("Simulation Starts...");
		print("Simulation ends, Output file created");

	}
}

Mode UI::getProgrammode() const
{
	return  programmode;
}

int UI::getinteger()
{
	int i;
	cin >> i;
	return i;

}

string UI::getstring()
{
	string s;
	cin >> s;
	return s;

}

void UI::PrintInfo(const Time& currenttime, Company* pCompany)
{
	
	cout << "Current Time (Day:Hour): " << currenttime.getday() << ":" << currenttime.gethour() << endl;
	printwaiting(pCompany);
	cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
	printloadingtrucks(pCompany);
	cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
	printemptytrucks(pCompany);
	cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
	printmoving(pCompany);
	cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
	printchecktrucks(pCompany);
	cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
	printdelivered(pCompany);
	cout << "-----------------------------------------------------------------------------------------------------------------------" << endl<< endl;
	

}
void UI::printwaiting(Company*pCompany)
{
	
	int numofwaiting = pCompany->getnumofwaiting();
	cout << numofwaiting << " Waiting Cargos: ";
	if (!pCompany->getnormalcargolist().isEmpty())
	{
		cout << "[";
		cout << pCompany->getnormalcargolist();
		cout << "] ";
	}
	if (!pCompany->getspecialcargolist().isEmpty())
	{
		cout << "(";
		cout << pCompany->getspecialcargolist();
		cout << ") ";
	}
	if (!pCompany->getVIPcargolist().isEmpty())
	{
		cout << "{";
		cout << pCompany->getVIPcargolist();
		cout << "} ";
	}
	cout<< endl;
}
void UI::printloadingtrucks(Company*pCompany)
{
	Truck* v=pCompany->getviploadingtruck();
	Truck* n= pCompany->getnormalloadingtruck();
	Truck* s=pCompany->getspecialloadingtruck();
	int numofloading = pCompany->getnumofloading();
	cout <<numofloading << " Loading Trucks: ";
	    if (n)
	    {
			
				cout << n->getTruckId();
				cout << "[";
				cout << n->getloadingcargos();
				cout << "] ";
		}
		if (s)
		{
			
				cout << s->getTruckId();
				cout << "(";
				cout << s->getloadingcargos();
				cout << ") ";
			
			
		}
		if (v)
		{
			
				cout << v->getTruckId();
				cout << "{";
				cout << v->getloadingcargos();
				cout << "} ";
			
		}
		
	
	cout << endl;
}
void UI::printemptytrucks(Company*pCompany)
{
	
	int numofemptytrucks = pCompany->getnumofemptytrucks();
	cout << numofemptytrucks << " Empty Trucks: ";
	if (!pCompany->getnormaltrucklist().isEmpty())
	{
		cout << "[";
		cout << pCompany->getnormaltrucklist();
		cout << "] ";
	}
	if (!pCompany->getspecialtrucklist().isEmpty())
	{
		cout << "(";
		cout << pCompany->getspecialtrucklist();
		cout << ") ";
	}
	if (!pCompany->getVIPtrucklist().isEmpty())
	{
		cout << "{";
		cout << pCompany->getVIPtrucklist();
		cout << "} ";
	}
	cout<< endl;
}


void UI::printmoving(Company* pCompany)
{
	int numofmoving = pCompany->getmovingcargosnum();
	cout << numofmoving << " Moving Cargos: ";
	cout << pCompany->getmovingtrucklist();
	cout<< endl;
	
}
void UI::printchecktrucks(Company*pCompany)
{
	
	int numofchecktrucks = pCompany->getnumofchecktrucks();
	cout << numofchecktrucks << " In-Checkup Trucks: ";
	if (!pCompany->getnormalchecktrucklist().isEmpty())
	{
		cout << "[";
		cout << pCompany->getnormalchecktrucklist();
		cout << "] ";
	}
	if (!pCompany->getspecialchecktrucklist().isEmpty())
	{
		cout << "(";
		cout << pCompany->getspecialchecktrucklist();
		cout << ") ";
	}
	if (!pCompany->getVIPchecktrucklist().isEmpty())
	{
		cout << "{";
		cout << pCompany->getVIPchecktrucklist();
		cout << "} ";
	}
	cout<< endl;
}
void UI::printdelivered(Company* pCompany)
{

	int numofdelivered = pCompany->getnumofdeliverd();
	cout << numofdelivered << " Delivered Cargos: ";
	if (!pCompany->getnormaldeliverdcargolist().isEmpty())
	{
		cout << "[";
		cout << pCompany->getnormaldeliverdcargolist();
		cout << "] ";
	}
	if (!pCompany->getspecialdeliverdcargolist().isEmpty())
	{
		cout << "(";
		cout << pCompany->getspecialdeliverdcargolist();
		cout << ") ";
	}
	if (!pCompany->getVIPdeliverdcargolist().isEmpty())
	{
		cout << "{";
		cout << pCompany->getVIPdeliverdcargolist();
		cout << "} ";
	}
    cout<<endl;

}

void UI::Setprogrammode()
{
	int x;
	do {
		cout << "Select The Program Mode: " << endl << "Enter 1 for Interactive , 2 for Step-by-Step or 3 for Silent Mode\n";
		cin >> x;
		if (x == 1)
		{
			programmode = Interactive;
		}
		else if (x == 2)
		{
			programmode = Stepbystep;
		}
		else if (x == 3)
		{
			programmode = Silent;
		}
		else
			cout << "Invalid input , Please Enter number 1,2 or 3\n";
	} while (x != 1 && x != 2 && x != 3);

}

void UI::print(string s)
{
	cout << s << endl;
}

void UI::end(Company*pCompany)
{
	print("Enter the file name to save data to it");
	string filename = getstring() + ".txt";
	pCompany->Save(filename);
	cout << "Data is saved to " << filename <<  endl;
}
