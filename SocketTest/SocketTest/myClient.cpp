#include "stdafx.h"
#include "mySocket.h"
#include "myLog.h"
#include "myException.h"
#include "myHostInfo.h"
#include "../../common/CommonAll.h"
#include "Serializer.h"

//myLog winLog;
void readServerConfig(string&);
void checkFileExistence(const string&);

void parseErrorCode(EErorCode err)
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

int main()
{
	// Initialize the winsock library
	myTcpSocket::initialize();
        
	// get client's information (assume neither the name nor the address is given)
	cout<<endl;
	cout<<"Retrieve the localHost [CLIENT] name and address:" << endl;
    myHostInfo clientInfo;
	string clientName = clientInfo.getHostName();
    string clientIPAddress = clientInfo.getHostIPAddress();
    cout << "Name: " << clientName << endl;
    cout << "Address: " << clientIPAddress << endl;
	cout<<"		==> Name: " << clientName << endl;
	cout<<"		==> Address: " << clientIPAddress << endl;

	// get server's IP address and name
	string serverIPAddress = "";
	readServerConfig(serverIPAddress);
	cout<<endl;
	cout<<"Retrieve the remoteHost [SERVER] name and address:" << endl;
	cout<<"		==> the given address is " << serverIPAddress << endl;

    myHostInfo serverInfo(serverIPAddress,ADDRESS);
	string serverName = serverInfo.getHostName();
    cout << "Name: " << serverName << endl;
    cout << "Address: " << serverIPAddress << endl;
	cout<<"		==> Name: " << serverName << endl;
	cout<<"		==> Address: " << serverIPAddress << endl;

    // create the socket for client
    myTcpSocket myClient(PORTNUM);
	cout << myClient;
	cout<<"client configuation: " << endl;
	cout<<myClient;

    // connect to the server.
	cout   << "connecting to the server [" << serverName << "] ... " << endl;
	cout<<"connecting to the server [" << serverName << "] ... " << endl;
	myClient.connectToServer(serverIPAddress,ADDRESS);
	ShowRegisterReq Req;

	int recvBytes = 0;
	int choice=-1;
	while (1)
	{
		// send message to server
		cout <<"\n================================\n";
		cout <<"\n================================\n";
		cout <<"\n================================\n";
		cout <<"Enter Your Choice==\n";
		cout <<"1 for Admin, To view the status..\n";
		cout <<"2 for Customer, To Book the ticket\n";
		cin>>choice;

		if(choice==1)
		{
			Req.m_showID=1;

			char messageToServer[MAX_MSG_LEN+1];
			memset(messageToServer,0,sizeof(messageToServer));
			cout << "[SEND] ";
			cin.getline(messageToServer,MAX_MSG_LEN);

			cout<<"[SEND] " << messageToServer << endl;

			ClientRequest Req;
			Req.m_reqType=ADMIN_VIEW;
			Req.m_showID=1;
			Req.m_ClientType=ADMIN;
			Req.m_userName="paurushk";
			Req.m_password="paurushk";
			
			string reqMsg=Serializer::SerilizeRequest(Req);

			cout<<"Mesg After Serealize =="<<reqMsg<<endl;

			myClient.sendMessage(reqMsg);
			if ( !string(messageToServer).compare("Quit") || !string(messageToServer).compare("quit") ) break;

			// receive message from server
			string messageFromServer = "";
			recvBytes = myClient.recieveMessage(messageFromServer);
			if ( recvBytes == -99 ) break;

			cout   << "[RECVED MESSAGE:" << serverName << "]: " << messageFromServer << endl;

			Response res=Serializer::DeSerilizeResponse(messageFromServer);

			parseErrorCode(res.retcode);
			cout<<"SHow Status==\n";
			cout<<res.seat_str<<endl;
		}
		else if (choice==2)
		{
			Req.m_showID=1;

			char messageToServer[MAX_MSG_LEN+1];
			memset(messageToServer,0,sizeof(messageToServer));
			cout << "[SEND] ";
			cin.getline(messageToServer,MAX_MSG_LEN);

			cout<<"[SEND] " << messageToServer << endl;

			ClientRequest Req;
			Req.m_reqType=BOOK_TICKET;
			Req.m_showID=1;
			Req.m_ClientType=CUSTOMER;
			Req.m_userName="paurushk";
			Req.m_password="paurushk";
			Req.m_seat.push_back(3);
			Req.m_seat.push_back(4);

			string reqMsg=Serializer::SerilizeRequest(Req);

			cout<<"Mesg After Serealize =="<<reqMsg<<endl;

			myClient.sendMessage(reqMsg);
			if ( !string(messageToServer).compare("Quit") || !string(messageToServer).compare("quit") ) break;

			// receive message from server
			string messageFromServer = "";
			recvBytes = myClient.recieveMessage(messageFromServer);
			if ( recvBytes == -99 ) break;

			//cout   << "[RECVED MESSAGE:" << serverName << "]: " << messageFromServer << endl;

			Response res=Serializer::DeSerilizeResponse(messageFromServer);

			parseErrorCode(res.retcode);
			cout<<"SHow Status==\n";
			cout<<res.seat_str<<endl;
		}
		else
		{
			cout<<"Wrong Choice, Please Enter again==\n";
		}
		
		
		

	}

    return 1;
}

void readServerConfig(string& serverIPAddr)
{
	//serverIPAddr=serverConfigIP;
	string serverConfigFile = "serverConfig.txt";	
	checkFileExistence(serverConfigFile);
	ifstream serverConfig(serverConfigFile.c_str());

	// read server's IP address
	getline(serverConfig,serverIPAddr);
	serverConfig.close();
}

void checkFileExistence(const string& fileName)
{
	ifstream file(fileName.c_str());
	if (!file) 
	{
		cout << "Cannot continue:" << fileName << " does NOT exist!" << endl;
		exit(1);
	}
	file.close();
}