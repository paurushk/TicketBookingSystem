#include "stdafx.h"
#include "../../common/TheaterShow.h"

void TheaterShow::DeIntilize()
{
			delete[] m_seat_status;
}
		

EErorCode TheaterShow::intilize(int theatreID, std::string theatreName, int numOfSeats)
		{
			EErorCode retCode=SUCCESS;
									
			 m_seat_status=new (nothrow) int [numOfSeats];
			 if(m_seat_status==nullptr)
			 {
				 retCode= SYS_NO_MEMORY_AVAILABLE;
			 }
			 else
			 {
				 for(int count=0; count<numOfSeats;count++)
				 {
					 m_seat_status[count]=-1;
				 }
				 m_availableSeats=numOfSeats;
				 m_showID=theatreID;
				 m_showname=theatreName;
				 m_numOfSeats=numOfSeats;
			 }

			 return retCode;
		}
		
string TheaterShow::getShowString()
{
	string out_str;

	for(int count=0; count<m_numOfSeats;count++)
	{
		char str[250]={0};
		if(m_seat_status[count]==-1)
			sprintf(str,"Seat-%d[Available]::",count+1);
		else
			sprintf(str,"Seat-%d[Booked]::",count+1);

		out_str.append(str);
	}
	return out_str;
}
void TheaterShow::showAvailableSeatLayout()
{
	for(int count=0; count<m_numOfSeats;count++)
	{
		if(m_seat_status[count]==-1)
			cout<<"Seat-"<<count+1<<"[Available]";
		else
			cout<<"Seat-"<<count+1<<"[Booked]";
	}
}

void TheaterShow::printShowInfo()
{
	cout<<"Total seats=="<<m_numOfSeats <<std::endl;
	cout<<"Available Seats=="<<m_availableSeats <<std::endl;
	cout<<"ShowName=="<<m_showname.c_str() <<std::endl;
	showAvailableSeatLayout();
}



EErorCode TheaterShow::bookTicket(vector <int> m_seat)
{
	EErorCode retCode=SUCCESS;
	if(m_availableSeats<m_seat.size())
	{
		retCode=NOT_ENOUGH_SEATS;
	}
	else
	{
		//std::cout << "myvector contains:\n";
		for (std::vector<int>::iterator it = m_seat.begin() ; it != m_seat.end(); ++it)
		{
			if(m_seat_status[*it-1]!=-1 || m_seat_status[*it-1]>m_numOfSeats)
			{
				retCode=REQUSTED_SEATS_ARE_ALREADY_BOOKED;
			}
		}
		if(retCode==SUCCESS)
		{
			for (std::vector<int>::iterator it = m_seat.begin() ; it != m_seat.end(); ++it)
			{
				m_seat_status[*it-1]=1;
			}
			m_availableSeats=m_availableSeats-m_seat.size();
		}
				
	}
	return retCode;
}