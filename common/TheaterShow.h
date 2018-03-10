#ifndef __THEATRE_THEATRE_SHOW_H__
#define __THEATRE_THEATRE_SHOW_H__

#include "../../common/CommonAll.h"

class TheaterShow
{
	private:
	 int m_showID;
	 int m_numOfSeats;
	 int *m_seat_status;
	 int m_availableSeats;
	 std::string m_showname;
	 void showAvailableSeatLayout();
	 //std::string m_showstr;

	public:
		TheaterShow()
		{
			m_seat_status=nullptr;
		}
		EErorCode intilize(int theatreID, std::string showName, int numOfSeats);
		void DeIntilize();
		EErorCode bookTicket(vector <int> m_seat);		
		void printShowInfo();
		string getShowString();

};

#endif ; //__THEATRE_THEATRE_SHOW_H__