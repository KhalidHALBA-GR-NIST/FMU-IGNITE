#define MODEL_IDENTIFIER drivecycle
#define MODEL_GUID "{8c4e810f-3df3-4a00-8276-176fa3c9f008}"
#define NUMBER_OF_REALS 4
#define NUMBER_OF_INTEGERS 1
#define NUMBER_OF_BOOLEANS 0
#define NUMBER_OF_STRINGS 0
#define NUMBER_OF_STATES 0
#define NUMBER_OF_EVENT_INDICATORS 0
#define BUFLEN 512	//Max length of buffer
#define PORT 8888	//The port on which to listen for incoming data
#include "fmuTemplate.h"
#include <winsock2.h>
#include <wS2tcpip.h>
#include <stdio.h> 
#include <windows.h>

#pragma comment( lib, "ws2_32.lib")
int xx = 0;

#include <stdlib.h> 
#include <string.h> 
#define cycle_speed_kmph_ 0
#define cycle_time_ahead_ 1
#define cycle_time_ 2
#define cycle_speed_ahead_kmph_ 3
#define counter_ 4
void setStartValues(ModelInstance *comp) {
    r(cycle_speed_kmph_) = 0;
    r(cycle_time_) = 0;
    r(cycle_speed_ahead_kmph_) = 0;
    r(cycle_time_ahead_) = 0;
    i(counter_) = 0;
}
fmiReal getReal(ModelInstance* comp, fmiValueReference vr){
    switch (vr) {
        case cycle_speed_kmph_ : return r(cycle_speed_kmph_);
        case cycle_time_ : return r(cycle_time_);
        case cycle_speed_ahead_kmph_ : return r(cycle_speed_ahead_kmph_);
        case cycle_time_ahead_ : return r(cycle_time_ahead_);
        default: return 0;
    }
}
void initialize(ModelInstance* comp, fmiEventInfo* eventInfo) {
    eventInfo->upcomingTimeEvent   = fmiTrue;
    eventInfo->nextEventTime       = 1 + comp->time;
}
void eventUpdate(ModelInstance* comp, fmiEventInfo* eventInfo) {


SOCKET s;
	struct sockaddr_in server, si_other;
	int slen , recv_len;
	char buf[BUFLEN];
	WSADATA wsa;

	slen = sizeof(si_other) ;
	
	//Initialise winsock
	// printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
	{
		// printf("Failed. Error Code : %d",WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	// printf("Initialised.\n");
	
	//Create a socket
	if((s = socket(AF_INET , SOCK_DGRAM , 0 )) == INVALID_SOCKET)
	{
		// printf("Could not create socket : %d" , WSAGetLastError());
	}
	// printf("Socket created.\n");
	
	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( PORT );
	
	//Bind
	if( bind(s ,(struct sockaddr *)&server , sizeof(server)) == SOCKET_ERROR)
	{
		// printf("Bind failed with error code : %d" , WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	puts("Bind done");

	//keep listening for data
    // try while(counter<value)


    i(counter_) += 1;

    if (i(counter_) > 2000) 
        eventInfo->terminateSimulation = fmiTrue;
    else {


        eventInfo->upcomingTimeEvent   = fmiTrue;
        eventInfo->nextEventTime       = 1 + comp->time;
    








	while(1)
	{
		// printf("Waiting for data...");
		fflush(stdout);
		
		//clear the buffer by filling null, it might have previously received data
		memset(buf,0, BUFLEN);
		
		//try to receive some data, this is a blocking call
		if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen)) == SOCKET_ERROR)
		{
			// printf("recvfrom() failed with error code : %d" , WSAGetLastError());
			exit(EXIT_FAILURE);
		}
		
        r(cycle_speed_kmph_)=(float)( atoi(buf));
		r(cycle_speed_ahead_kmph_)=(float)( atoi(buf) + (rand()%5) );

		//print details of the client/peer and the data received
		// printf("Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
		 printf("Data: %f %f %d\n" ,  r(cycle_speed_kmph_),  r(cycle_speed_ahead_kmph_),  i(counter_));
		
		// //now reply the client with the same data
		// if (sendto(s, buf, recv_len, 0, (struct sockaddr*) &si_other, slen) == SOCKET_ERROR)
		// {
		// 	printf("sendto() failed with error code : %d" , WSAGetLastError());
		// 	exit(EXIT_FAILURE);
		// }
	
    break;
//try without break

    }


}
	closesocket(s);
	WSACleanup();
	
	return;






    // r(cycle_speed_kmph_)=(float)(rand() % 50 );

    //  printf("OK  %f \n",r(cycle_speed_kmph_));



















































 }
#include "fmuTemplate.c"