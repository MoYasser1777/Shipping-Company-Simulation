#pragma once
#include <fstream>
#include <iostream>
using namespace std;
#include <string>
#include "types.h"
#include "Time.h"
#include "Company.h"
#include"Queue.h"
#include"perQueue.h"
#include <string>
#include<windows.h>
class Company;


class UI
{
	Mode programmode;

public:

	UI();
	void start(Company*pCompany);//calls load function and set program mode(interactive,step by step,silent)
	void simulate(Company*pCompany);//updates time every hour and call update function from company
	Mode getProgrammode()const;
	int getinteger();
	string getstring();
	void PrintInfo(const Time& currenttime, Company* pCompany);
	void printwaiting(Company* pCompany);
	void printloadingtrucks(Company* pCompany);
	void printemptytrucks(Company* pCompany);
	void printmoving(Company* pCompany);
	void printchecktrucks(Company* pCompany);
	void printdelivered(Company* pCompany);
	void Setprogrammode();
	void print(string s);
	void end(Company* pCompany);// called when the simulation ends and call save function

};

