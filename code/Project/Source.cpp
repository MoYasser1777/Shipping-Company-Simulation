#include<iostream>
using namespace std;
#include<windows.h>
#include"Queue.h"
#include"Event.h"
#include"Cargo.h"
#include"perQueue.h"
#include"UI.h"



int main()
{
	Company shippingcompany;//create a company object
	
	UI* pUI = shippingcompany.getUI();

	pUI->start(&shippingcompany);
	
	pUI->simulate(&shippingcompany);
	
	pUI->end(&shippingcompany);
	
	return 0;
}