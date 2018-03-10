#ifndef __THEATRE_SERIALIZE_SHOW_H__
#define __THEATRE_SERIALIZE_SHOW_H__

#include "../../common/CommonAll.h"

class Serializer
{
	static void tokenize(const string& str, vector<string>& tokens, const string& delimiters = ",")
		{
		  // Skip delimiters at beginning.
		  string::size_type lastPos = str.find_first_not_of(delimiters, 0);

		  // Find first non-delimiter.
		  string::size_type pos = str.find_first_of(delimiters, lastPos);

		  while (string::npos != pos || string::npos != lastPos) 
			  {
				// Found a token, add it to the vector.
				tokens.push_back(str.substr(lastPos, pos - lastPos));

				// Skip delimiters.
				lastPos = str.find_first_not_of(delimiters, pos);

				// Find next non-delimiter.
				pos = str.find_first_of(delimiters, lastPos);
			  }
		}

	public:
		static std::string EncodeVector(ClientRequest Req)
		{
			/*if(m_seat_status[count]==-1)
				cout<<"Seat-"<<count+1<<"[Available]";
			else
				cout<<"Seat-"<<count+1<<"[Booked]";*/
			std::string seatRequest="";
			char seat[10]={0};
			for (std::vector<int>::iterator it = Req.m_seat.begin() ; it != Req.m_seat.end(); ++it)
			{
				if(*it==-1)
					sprintf(seat,"Seat-%d{Available}:",*it);
				else
					sprintf(seat,"Seat-%d{Booked}:",*it);

				seatRequest.append(seat);
			}

			//seatRequest.append("]");
			return seatRequest;
		}

		static std::string EncodeReqVector(ClientRequest Req)
		{
			/*if(m_seat_status[count]==-1)
				cout<<"Seat-"<<count+1<<"[Available]";
			else
				cout<<"Seat-"<<count+1<<"[Booked]";*/
			std::string seatRequest="";
			char seat[10]={0};
			for (std::vector<int>::iterator it = Req.m_seat.begin() ; it != Req.m_seat.end(); ++it)
			{
				sprintf(seat,"%d:",*it);

				seatRequest.append(seat);
			}

			//seatRequest.append("]");
			return seatRequest;
		}
		static std::string SerilizeRequest(ClientRequest Req)
		{
			char reqStr[MAX_REQ_SIZE]={0};
			//std::string vect_string=EncodeReqVector(Req);
			string reqString="";
			if(!Req.seat_str.empty())
			{
				Req.convertVectortoString();
				sprintf(reqStr,"%d,%d,%d,%s,%s,%s",Req.m_reqType,Req.m_ClientType,Req.m_showID,
					Req.m_userName.c_str(),Req.m_password.c_str(),Req.seat_str.c_str());
			}
			else
			{
				Req.convertVectortoString();
				//Req.seat_str="";
				sprintf(reqStr,"%d,%d,%d,%s,%s,%s",Req.m_reqType,Req.m_ClientType,Req.m_showID,
				Req.m_userName.c_str(),Req.m_password.c_str(),Req.seat_str.c_str());
			}
			
			reqString.append(reqStr);
			return reqString;
			//reqStr.append(std::to_string(Req.m_ClientType));
		}

		static ClientRequest DeSerilizeRequest(std::string reqStr)
		{
			ClientRequest Req;
			 char *pt;
			 string delim=",";
			 vector<string> tokens;
			 tokenize(reqStr, tokens, delim);
			 int count=1;
			 for (std::vector<string>::iterator it = tokens.begin() ; it != tokens.end(); ++it)
			{
				if(count==1)
				{
					const char *reqType=it->c_str();
					Req.m_reqType=(EReqType)atoi(reqType);
				}
				else if(count==2)
				{
					const char *val=it->c_str();
					Req.m_ClientType=(EClientType)atoi(val);
				}
				else if(count==3)
				{
					const char *val=it->c_str();
					Req.m_showID=atoi(val);
				}
				else if(count==4)
				{
					Req.m_userName=*it;
				}
				else if(count==5)
				{
					Req.m_password=*it;
				}
				else if(count==6)
				{
					Req.seat_str=*it;
				}
				count++;
			 }
			 Req.convertStringtoVector(":");

			 return Req;
		}
		
		static std::string SerilizeResponse(Response Res)
		{
			char reqStr[1024]={0};
			//std::string vect_string=EncodeReqVector(Req);
			string reqString="";
			//Req.convertVectortoString();
			sprintf(reqStr,"%d,%s",Res.retcode,Res.seat_str.c_str());
			reqString.append(reqStr);
			return reqString;
		}

		static Response DeSerilizeResponse(std::string reqStr)
		{
			Response Res;
			 char *pt;
			 string delim=",";
			 vector<string> tokens;
			 tokenize(reqStr, tokens, delim);
			 int count=1;
			 for (std::vector<string>::iterator it = tokens.begin() ; it != tokens.end(); ++it)
			{
				
				if(count==1)
				{
					const char *reqType=it->c_str();
					Res.retcode=(EErorCode)atoi(reqType);
				}
				else if(count==2)
				{
					const char *val=it->c_str();
					Res.seat_str=val;
				}
				count++;
			 }
			 return Res;
		}


};

#endif ; //__THEATRE_SERIALIZE_SHOW_H__