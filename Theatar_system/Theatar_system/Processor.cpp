#include "stdafx.h"
#include "Processor.h"
#include "TheaterInterface.h"
#include "TheaterBookingEngine.h"

EErorCode Processor::Process(ClientRequest Req,Response *res)
{
	ITheatreUser* user= TheatreUserFactory::createTheatreFactory(Req);
	EErorCode retCode=UNKNOWN_ERROR;
	if(user==NULL)
	{
		retCode = UNIDENTIFIED_CLIENT;
	}
	else
		retCode= user->validateandProcess(Req,res);

	delete user;
	return retCode;
}

void Processor::printErrorCode(EErorCode err)
{
	cout<<"\n";
	if(err==UNKNOWN_ERROR)
	{
		cout<<"Result is  UNKNOWN_ERROR \n";
	}
	else if(err==INVALID_REQUEST)
	{
		cout<<"Result is  INVALID_REQUEST \n";
	}
	else if(err==SUCCESS)
	{
		cout<<"Result is  SUCCESS \n";
	}
	else if(err==UNIDENTIFIED_CLIENT)
	{
		cout<<"Result is  UNIDENTIFIED_CLIENT \n";
	}
	else if(err==INVALID_AUTHENTICATION)
	{
		cout<<"Result is  INVALID_AUTHENTICATION \n";
	}
	else if(err==INVALID_NUMBER_OF_SEAT_REQUSTED)
	{
		cout<<"Result is  INVALID_NUMBER_OF_SEAT \n";
	}
	else if(err==REQUSTED_SEATS_ARE_ALREADY_BOOKED)
	{
		cout<<"Result is  REQUSTED_SEATS_ARE_ALREADY_BOOKED \n";
	}
	else
	{
		cout<<"FATAL Error is Not Defined \n";
	}
	

}

void Processor::test()
{
	cout<<"TestCase1-->testing Admin\n";

	ClientRequest Req;
	Req.m_ClientType=ADMIN;
	Req.m_reqType=ADMIN_VIEW;
	Req.m_userName="paurushk";
	Req.m_password="paurushk";
	Req.m_showID=2;
	Response res;

	EErorCode errCode= Processor::Process(Req,&res);
	
	printErrorCode(errCode);
	res.show->printShowInfo();
}

void Processor::test1()
{
	cout<<"TestCase1-->testing Admin uthentication successful\n";

	ClientRequest Req;
	Req.m_ClientType=ADMIN;
	Req.m_reqType=ADMIN_VIEW;
	Req.m_userName="paurushk";
	Req.m_password="paurushk";
	Req.m_showID=1;
	Response res;

	EErorCode errCode= Processor::Process(Req,&res);
	
	printErrorCode(errCode);
	res.show->printShowInfo();

	if(errCode==SUCCESS)
	{	
		cout<<"testCase is successful \n";
	}
	else
	{
		cout<<"testCase is not successful \n";
	}

	cout<<"testing Admin CLient password successful\n\n";

	
	Req.m_ClientType=ADMIN;
	Req.m_reqType=ADMIN_VIEW;
	Req.m_userName="paurushk";
	Req.m_password="paurush";

	errCode= Processor::Process(Req,&res);
	printErrorCode(errCode);
	if(errCode==INVALID_AUTHENTICATION)
	{	
		cout<<"testCase is successful \n";
	}
	else
	{
		cout<<"testCase is not successful \n";
	}

cout<<"\nTestCase3-->testing Admin CLient invalid Request\n";

	Req.m_ClientType=ADMIN;
	Req.m_reqType=BOOK_TICKET;
	Req.m_userName="paurushk";
	Req.m_password="paurushk";

	errCode= Processor::Process(Req,&res);
	printErrorCode(errCode);
	if(errCode==INVALID_REQUEST)
	{	
		cout<<"testCase is successful \n";
	}
	else
	{
		cout<<"testCase is not successful \n";
	}


	cout<<"\nTestCase4-->testing Customer CLient Valid Request\n";

	Req.m_ClientType=CUSTOMER;
	Req.m_reqType=BOOK_TICKET;
	Req.m_seat.push_back(1);
	Req.m_seat.push_back(2);
	Req.m_seat.push_back(3);
	

	errCode= Processor::Process(Req,&res);
	printErrorCode(errCode);
	if(errCode==SUCCESS)
	{	
		cout<<"testCase is successful \n";
	}
	else
	{
		cout<<"testCase is not successful \n";
	}

	cout<<"\nTestCase5-->testing Customer CLient InValid Request\n";

	Req.m_ClientType=CUSTOMER;
	Req.m_reqType=ADMIN_VIEW;
	Req.m_seat.push_back(1);
	Req.m_seat.push_back(2);
	Req.m_seat.push_back(3);
	

	errCode= Processor::Process(Req,&res);
	printErrorCode(errCode);
	if(errCode==INVALID_REQUEST)
	{	
		cout<<"testCase is successful \n";
	}
	else
	{
		cout<<"testCase is not successful \n";
	}

	cout<<"\nTestCase5-->testing Customer CLient InValid Request\n";

	Req.m_ClientType=CUSTOMER;
	Req.m_reqType=ADMIN_VIEW;
	Req.m_seat.clear();
	
	cout<<"size of \n"<<Req.m_seat.size()<<"\n" ;
	errCode= Processor::Process(Req,&res);
	printErrorCode(errCode);
	if(errCode==INVALID_NUMBER_OF_SEAT_REQUSTED)
	{	
		cout<<"testCase is successful \n";
	}
	else
	{
		cout<<"testCase is not successful \n";
	}
}

void Processor::testbookingEngine()
{
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
	
	printErrorCode(retcode);

	ClientRequest request;
	
	request.m_showID=2;
	request.m_seat.clear();
	request.m_seat.push_back(2);
	request.m_seat.push_back(3);

	retcode=TheaterBookingEngine::getTheaterBookingEngine()->bookSeatsTheaterShow(request);

	request.Clear();
	
	request.m_showID=1;
	request.m_seat.clear();
	request.m_seat.push_back(7);
	request.m_seat.push_back(8);

	retcode=TheaterBookingEngine::getTheaterBookingEngine()->bookSeatsTheaterShow(request);

	if(retcode==SUCCESS)
	{
		cout<<"Theator show is registered"<<endl;
		retcode=TheaterBookingEngine::getTheaterBookingEngine()->TraverseTheaterShows();
	}
	printErrorCode(retcode);
}


