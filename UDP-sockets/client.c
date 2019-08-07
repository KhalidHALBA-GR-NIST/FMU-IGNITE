/*
	Simple udp client
*/
#include<stdio.h>
#include<winsock2.h>
#pragma comment(lib,"ws2_32.lib") //Winsock Library

#define SERVER "127.0.0.1"	//ip address of udp server
#define BUFLEN 512	//Max length of buffer
#define PORT 8888	//The port on which to listen for incoming data

int main(void)
{
	struct sockaddr_in si_other;
	int s, slen=sizeof(si_other);
	char buf[BUFLEN];
	char message[BUFLEN];
	WSADATA wsa;

	//Initialise winsock
	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
	{
		printf("Failed. Error Code : %d",WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	printf("Initialised.\n");
	
	//create socket
	if ( (s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR)
	{
		printf("socket() failed with error code : %d" , WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	
	//setup address structure
	memset((char *) &si_other, 0, sizeof(si_other));
	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(PORT);
	si_other.sin_addr.S_un.S_addr = inet_addr(SERVER);
	
	//start communication
	while(1)
	{
	





  //  printf("Connected to server!\n");
 static const char filename[] = "C:\\Users\\KHALID HALBA\\Desktop\\UDP-FMU\\UDP-sockets\\FTP75.txt";
   FILE *file = fopen ( filename, "r" );
   if ( file != NULL )
   {
      char line [10]; /* or other suitable maximum line size */
     // char drivecycle[] =   strcat(line, line);
 
int t = 0;
      while ( fgets ( line, sizeof line, file ) != NULL ) /* read a line */
      {
 Sleep(1000);
float eee = atof(line);
printf("speed %f \n", eee);
char spd[10];
sprintf(spd, "%f", eee);
const char* speed = spd;



		//send the message
		if (sendto(s, speed, strlen(speed) , 0 , (struct sockaddr *) &si_other, slen) == SOCKET_ERROR)
		{
			printf("sendto() failed with error code : %d" , WSAGetLastError());
			exit(EXIT_FAILURE);
		}
		




      }
      fclose ( file );
   }
   else
   {
      perror ( filename );
   }















































		
		puts(buf);
	}

	closesocket(s);
	WSACleanup();

	return 0;
}






