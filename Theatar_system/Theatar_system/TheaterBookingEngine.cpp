#include "stdafx.h"
#include "TheaterBookingEngine.h"

TheaterBookingEngine* TheaterBookingEngine::myInstance=NULL;
HANDLE TheaterBookingEngine::m_Mutex=NULL;


TheaterBookingEngine* TheaterBookingEngine::getTheaterBookingEngine()
{
	if(myInstance==NULL)
	{
		myInstance=new TheaterBookingEngine();
		myInstance->init();
	}
	return myInstance;
}

void TheaterBookingEngine::init()
{
	m_Mutex = CreateMutex( 
        NULL,              // default security attributes
        FALSE,             // initially not owned
        NULL);             // unnamed mutex

    if (m_Mutex == NULL) 
    {
        printf("CreateMutex error: %d\n", GetLastError());
        return;
    }
	//m_Mutex
}

void TheaterBookingEngine::deinit()
{
	CloseHandle(m_Mutex);
	//
}



EErorCode TheaterBookingEngine::bookSeatsTheaterShow(ClientRequest request)
{
	DWORD dwWaitResult = WaitForSingleObject( 
            m_Mutex,    // handle to mutex
            INFINITE);  // no time-out interval

	if(dwWaitResult!=WAIT_OBJECT_0)
	{
		ReleaseMutex(m_Mutex);
		return SYS_ERROR;
	}
	EErorCode retCode=SUCCESS;
	if(request.m_showID<=0)
	{
		retCode= INVALID_THEATRE_ID;	
	}
	else if(request.m_seat.size()<=0)
	{
		retCode= INVALID_NUMBER_OF_SEAT_REQUSTED;
	}
	
	std::map<int, TheaterShow*>::iterator it = m_theaterShows.find(request.m_showID);
	if( it!= m_theaterShows.end())
	{
		TheaterShow* show=it->second;
		retCode=show->bookTicket(request.m_seat);	
	}
	else
			retCode= SHOW_NOT_EXIST;	

	ReleaseMutex(m_Mutex);
	return retCode;
}

TheaterShow* TheaterBookingEngine::getshow(int showid)
{
	DWORD dwWaitResult = WaitForSingleObject( 
            m_Mutex,    // handle to mutex
            INFINITE);  // no time-out interval

	if(dwWaitResult!=WAIT_OBJECT_0)
	{
		ReleaseMutex(m_Mutex);
		return nullptr;
	}

	TheaterShow* show=NULL;

	std::map<int, TheaterShow*>::iterator it = m_theaterShows.find(showid);
	if( it!= m_theaterShows.end())
	{
		show=it->second;
	}
	
	ReleaseMutex(m_Mutex);
	return show;
}

EErorCode TheaterBookingEngine::deleteTheaterShow(int showid)
{
	DWORD dwWaitResult = WaitForSingleObject( 
            m_Mutex,    // handle to mutex
            INFINITE);  // no time-out interval

	if(dwWaitResult!=WAIT_OBJECT_0)
	{
		ReleaseMutex(m_Mutex);
		return SYS_ERROR;
	}
	EErorCode retCode=SUCCESS;
	if(m_theaterShows.find(showid) != m_theaterShows.end())
			{
				//m_theaterShows.insert(std::make_pair(regRequest.m_showID, newshow));
				m_theaterShows.erase(showid);
			}
			else
				retCode= SHOW_NOT_EXIST;

	ReleaseMutex(m_Mutex);
	return retCode;
}

EErorCode TheaterBookingEngine::TraverseTheaterShows()
{
	// Iterate through all elements in std::map
    std::map<int, TheaterShow*>::iterator it = m_theaterShows.begin();
    while(it != m_theaterShows.end())
    {
		TheaterShow* show=it->second;
        cout<<"showID=="<<it->first<<endl;
		show->printShowInfo();
		it++;
    }
	return SUCCESS;
}

EErorCode TheaterBookingEngine::RegisterTheaterShow(ShowRegisterReq regRequest)
{
	DWORD dwWaitResult = WaitForSingleObject( 
            m_Mutex,    // handle to mutex
            INFINITE);  // no time-out interval

	if(dwWaitResult!=WAIT_OBJECT_0)
	{
		ReleaseMutex(m_Mutex);
		return SYS_ERROR;
	}
	EErorCode retCode=SUCCESS;
	if(regRequest.m_showID<=0)
	{
		retCode= INVALID_THEATRE_ID;	
	}
	else if(regRequest.m_numOfSeats<=0)
	{
		retCode= INVALID_NUMBER_OF_SEAT_IN_THEATRE;
	}
	TheaterShow *newshow= new (nothrow)TheaterShow();
			
	if(newshow==nullptr)
		{
			retCode= SYS_NO_MEMORY_AVAILABLE;
		}

	retCode=newshow->intilize(regRequest.m_showID, regRequest.name, regRequest.m_numOfSeats);
	if(retCode!=SUCCESS)
	{
			retCode= retCode;
	}
	else
	{
			if(m_theaterShows.find(regRequest.m_showID) == m_theaterShows.end())
			{
				m_theaterShows.insert(std::make_pair(regRequest.m_showID, newshow));
			}
			else
				retCode= SHOW_ALREADY_EXIST;
	}
	ReleaseMutex(m_Mutex);
	return retCode;
}

