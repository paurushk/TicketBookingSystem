// Theatar_system.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include "Processor.h"
#include "TheaterBookingEngine.h"



using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	cout<< "Hello world\n";
	//Processor::test1();
	ShowRegisterReq regRequest;
	regRequest.m_showID=1;
	regRequest.m_numOfSeats=10;
	regRequest.name="TeleDNASHow";
	EErorCode retcode=TheaterBookingEngine::getTheaterBookingEngine()->RegisterTheaterShow(regRequest);


	regRequest.Clear();
	regRequest.m_showID=2;
	regRequest.m_numOfSeats=5;
	regRequest.name="MObileum";
	retcode=TheaterBookingEngine::getTheaterBookingEngine()->RegisterTheaterShow(regRequest);

	if(retcode==SUCCESS)
	{
		cout<<"Theator show is registered"<<endl;
		retcode=TheaterBookingEngine::getTheaterBookingEngine()->TraverseTheaterShows();
	}


	Processor::test();
	getch();
	return 0;
}




