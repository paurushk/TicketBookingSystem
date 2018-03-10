#ifndef __THEATRE_BOOKINENGINE_H__
#define __THEATRE_BOOKINENGINE_H__

#include "../../common/CommonAll.h"
#include "../../common/TheaterShow.h"
#include <windows.h>

class TheaterBookingEngine
{
	private:
		TheaterBookingEngine()
		{
		}
		~TheaterBookingEngine()
		{
		}
		map<int, TheaterShow*> m_theaterShows;

		static HANDLE m_Mutex; 
		static void init();
		static void deinit();

	public:
		static TheaterBookingEngine *myInstance;
		static TheaterBookingEngine *getTheaterBookingEngine();	
		EErorCode RegisterTheaterShow(ShowRegisterReq regRequest);
		EErorCode TraverseTheaterShows();
		EErorCode deleteTheaterShow(int showid);
		EErorCode bookSeatsTheaterShow(ClientRequest request);
		TheaterShow* getshow(int showid);

};

#endif //__THEATRE_BOOKINENGINE_H__