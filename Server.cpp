#include "stdafx.h"
#define PORT 5735
SOCKET sServer;

unsigned long GetLocalIP()
{
	char szHostName[256];
	struct hostent * pHost;
	// Get host adresses
	gethostname(szHostName, 255);
	pHost = gethostbyname(szHostName);
	return *((unsigned long*)pHost->h_addr_list[0]);
}

void SetupServer(char *IPStr)
{
	WSADATA ws;
	long lResult;
	sockaddr_in addrServer;

	// start sock environment
	lResult = WSAStartup(0x0101,&ws);
	
	// ---- build server ----
	addrServer.sin_family=AF_INET;
	addrServer.sin_port=htons(PORT);
	sServer=socket(AF_INET,SOCK_STREAM,0);
	if(IPStr==NULL)	addrServer.sin_addr.s_addr=GetLocalIP();
	else addrServer.sin_addr.s_addr=inet_addr(IPStr);
	// bind
	if(bind(sServer,(sockaddr *)&addrServer,sizeof(sockaddr_in))!=0)
	{
		printf("Fatal Error:Can't build server %i.%i.%i.%i at port %d!\n",
			addrServer.sin_addr.S_un.S_un_b.s_b1,
			addrServer.sin_addr.S_un.S_un_b.s_b2,
			addrServer.sin_addr.S_un.S_un_b.s_b3,
			addrServer.sin_addr.S_un.S_un_b.s_b4,
			PORT);
		exit(NULL);
	}
	printf("Build server %i.%i.%i.%i at port %d.\n",
		addrServer.sin_addr.S_un.S_un_b.s_b1,
		addrServer.sin_addr.S_un.S_un_b.s_b2,
		addrServer.sin_addr.S_un.S_un_b.s_b3,
		addrServer.sin_addr.S_un.S_un_b.s_b4,
		PORT);
	// listen
	listen(sServer,5);
}
