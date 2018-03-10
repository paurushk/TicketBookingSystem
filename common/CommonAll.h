#ifndef __THEATRE_SYSTEM_COMMON_H__
#define __THEATRE_SYSTEM_COMMON_H__
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <map>
#include <string>


//#include "TheaterBookingEngine.h"



using namespace std;

//Config Section start
const std:: string userName="paurushk" ;
const std:: string password="paurushk" ;
//const std:: string serverConfigIP="192.168.0.103";
const int PORTNUM = 1200;


//COnfig Section ENd

 #define MAX_REQ_SIZE 4096

enum EClientType
{
  UNKNOWN_CLIENT = -1,
  CUSTOMER = 0,
  ADMIN,
};

enum EReqType
{
	UNKNOWN_REQUEST = -1,
    ADMIN_VIEW = 0,
	BOOK_TICKET,
};

enum EErorCode
{
	UNKNOWN_ERROR = -1,
    INVALID_REQUEST = 0,
	SUCCESS,
	UNIDENTIFIED_CLIENT,
	INVALID_AUTHENTICATION,
	INVALID_NUMBER_OF_SEAT_REQUSTED,
	INVALID_NUMBER_OF_SEAT_IN_THEATRE,
	INVALID_THEATRE_ID,
	INVALID_THEATRE_NAME,
	SYS_NO_MEMORY_AVAILABLE,
	NOT_ENOUGH_SEATS,
	REQUSTED_SEATS_ARE_ALREADY_BOOKED,
	SHOW_ALREADY_EXIST,
	SHOW_NOT_EXIST,
	SYS_ERROR,

};

class TheaterShow;
struct Response
{
	EErorCode retcode;
	TheaterShow* show;
	string seat_str;
	void clear()
	{
		retcode=UNKNOWN_ERROR;
		show=NULL;
		seat_str="";
	}
};

struct ShowRegisterReq
{
	 int m_showID;
	 int m_numOfSeats;
	 std::string name;
	 void Clear()
	 {
		 m_showID=-1;
		 m_numOfSeats=-1;
		 name="";
	 }
};

struct ClientRequest
{
  EClientType  m_ClientType;
  std::string m_userName;
  std::string m_password;
  vector <int> m_seat;
  std::string seat_str;
  EReqType m_reqType;
  int m_showID;
	
  
	void convertVectortoString()
		{
			/*if(m_seat_status[count]==-1)
				cout<<"Seat-"<<count+1<<"[Available]";
			else
				cout<<"Seat-"<<count+1<<"[Booked]";*/
			//std::string seatRequest="";
			char seat[10]={0};
			for (std::vector<int>::iterator it = m_seat.begin() ; it != m_seat.end(); ++it)
			{
				sprintf(seat,"%d:",*it);

				seat_str.append(seat);
			}
		}

    void convertStringtoVector( const string& delimiters = ",")
		{
			//const string& str, vector<string>& tokens,
		  // Skip delimiters at beginning.
		  string::size_type lastPos = seat_str.find_first_not_of(delimiters, 0);

		  // Find first non-delimiter.
		  string::size_type pos = seat_str.find_first_of(delimiters, lastPos);

		  while (string::npos != pos || string::npos != lastPos) 
			  {
				// Found a token, add it to the vector.
				string temp=seat_str.substr(lastPos, pos - lastPos);
				m_seat.push_back(atoi(temp.c_str()));

				// Skip delimiters.
				lastPos = seat_str.find_first_not_of(delimiters, pos);

				// Find next non-delimiter.
				pos = seat_str.find_first_of(delimiters, lastPos);
			  }
		}

  void Clear()
  {
     m_ClientType=UNKNOWN_CLIENT;
	m_userName="";
	m_password="";
	m_seat.clear();
	m_reqType=UNKNOWN_REQUEST;
	m_showID=-1;
  }

}; //STDejaChatTunnelAuxInfo





#endif //__THEATRE_SYSTEM_COMMON_H__