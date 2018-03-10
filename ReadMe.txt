##########
##ReadMe##
##########

1. Code Description
	a.SocketTest folder consist client Code
	b.Theatar_system folder consist server Code
	c.Binary folder consist binaries(client and server), serverConfig.txt have IP need to configured.
	d. common folder have common code needed for client and server.


2. Main points Code and Design 
	a.Theatar_system works as server and can connect to 5 multiple clients simultaneously, synchronized through a semaphore.

	b.Multiple thread will invoked as per multiple client requested.

	c.Socket communication is interpret through request and response structures defined in CommonAll.h. This aloes includes other common items required for client and server.

	d.Serializer.h contains serialize and reserialize for request and response over socket.

	c.TheaterInterface class is an interface to connect with theatre booking engine. 
		1. This is implemented through factory based design pattern for Admin and customer
		2. further carries the authentication and other necessary checks depending upon user type.

	f.TheaterBookingEngine is thread safe singleton class have the map for all registered shows., supports below functionalities
		1.Registering the shows
		2.View the status of show
		3.Book the ticks.
		4.Delete the shows


3. Limitation: 
	a. System is not persistent an so if process gets restarted, all data will get vanished.
	b.  All configuration are almost compile time(other then IP) and available in code section of "E:\Learning\TeleDNA\common\CommonAll.h".
	c. Registering theater system is also through compile time.
	d. limited operation(view the seat booking status, book the ticket(3rd and 4th seat)) are exposed to user.


4. how to Run: 
	a. Configure serverConfig.txt with IP address
	b. Run "Binary/Theatar_system.exe"
	c. Run "SocketTest.exe"
	d. enter option 1 or 2 at console of "SocketTest.exe", 
		<1> for Admin, To view the status
		<2> for Customer, To Book the ticket(always 3rd and 4th ticket will be booked, actually govern by main() function myClient.cpp)
		<quit> for quitting the client.

5. Socket Code is borrowed from internet and tuned according our requirement.