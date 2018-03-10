#ifndef __THEATRE_INTERFACE_H__
#define __THEATRE_INTERFACE_H__

/////////////////////////////////////////////////////////////////////////////////////////////
// 
//																		
//////////////////////////////////////////////////////////////////////////////////////////////

#include "../../common/CommonAll.h"


class ITheatreUser
{
	private:
	 EClientType  m_ClientType;
	 EReqType m_reqType;
  public:
	   ITheatreUser( )
	  {
	  }
	  
	  ITheatreUser( EClientType clientType,EReqType reqType):m_ClientType(clientType),m_reqType(reqType)
	  {
	  }

	  virtual ~ITheatreUser( )
	  {
	  }


	  virtual EErorCode validateandProcess(ClientRequest Req,Response *res)=0;
}; 

class AdminUser:public ITheatreUser
{
	private:
	 const std::string m_userName;
	 const std::string m_password;

	public:
		AdminUser():m_userName(userName),m_password(password)
		{
		}

		AdminUser(EClientType clientType,EReqType reqType):ITheatreUser(clientType,reqType),m_userName(userName),m_password(password)
		{
		}
		
		EErorCode validateandProcess(ClientRequest Req,Response *res);
			
};

class CustomerUser:public ITheatreUser
{
	public:
		CustomerUser()
		{
		}

		CustomerUser(EClientType clientType,EReqType reqType):ITheatreUser(clientType,reqType)
		{
		}
		
		EErorCode validateandProcess(ClientRequest Req,Response *res);
			
};

class TheatreUserFactory
{
	public:
		static ITheatreUser* createTheatreFactory(ClientRequest Req)
		{
			ITheatreUser* user=NULL;
			if(Req.m_ClientType==ADMIN)
			{
				user= new AdminUser(Req.m_ClientType,Req.m_reqType);
			}
			else if(Req.m_ClientType==CUSTOMER)
			{
				user= new CustomerUser(Req.m_ClientType,Req.m_reqType);
			}
			return user;
		}
			
};

#endif //__THEATRE_INTERFACE_H__