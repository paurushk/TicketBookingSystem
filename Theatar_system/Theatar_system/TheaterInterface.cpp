#include "stdafx.h"
#include "TheaterInterface.h"
#include "TheaterBookingEngine.h"


EErorCode AdminUser::validateandProcess(ClientRequest Req,Response *res)
			{
				cout<<"UserName-->"<<m_userName.c_str()<<"\n";
				cout<<"Password-->"<<m_userName.c_str()<<"\n";

				EErorCode retCode=UNKNOWN_ERROR;
				if(Req.m_userName.compare(m_userName)==0
					&& Req.m_password.compare(m_password)==0)
				{
					cout<<"Amdin Authentication Succesfull\n";
				}
				else
				{
					retCode= INVALID_AUTHENTICATION ;
					return retCode;
				}

				if(Req.m_reqType == ADMIN_VIEW)
				{
					//cout<<"Amdin Authentication Succesfull\n" ;
					//code for viewing the ticket
					TheaterShow* show=TheaterBookingEngine::getTheaterBookingEngine()->getshow(Req.m_showID);
					if(show==NULL)
					{
						return SHOW_NOT_EXIST;
					}
					
					retCode= SUCCESS;
					
					res->retcode=retCode;
					res->show=show;
					res->seat_str=show->getShowString();
				}
				else
					retCode= INVALID_REQUEST;

				

				return retCode;
		}

EErorCode CustomerUser::validateandProcess(ClientRequest Req,Response *res)
{
	EErorCode retCode=SUCCESS;
		if(Req.m_seat.size()<=0)
		{
			retCode= INVALID_NUMBER_OF_SEAT_REQUSTED;
		}
		else if(Req.m_reqType==BOOK_TICKET)
		{
			retCode=TheaterBookingEngine::getTheaterBookingEngine()->bookSeatsTheaterShow(Req);

			if(retCode==SUCCESS)
			{
				cout<<"Theator show is registered"<<endl;
				retCode=TheaterBookingEngine::getTheaterBookingEngine()->TraverseTheaterShows();
			}
			//retCode= SUCCESS;
			res->retcode=retCode;
			res->show=TheaterBookingEngine::getTheaterBookingEngine()->getshow(Req.m_showID);
			res->seat_str=res->show->getShowString();

		}
		else
			retCode = INVALID_REQUEST;

		return retCode;

}