#include "stdafx.h"
using namespace std;
void SetupServer(char *IPStr);
char longstr[]="HTTP/1.1 200 OK\nContent-Type:text/html;charset=GBK\nConnection: Close\n\n<html><head><meta content=\"text/html; charset=GBK\"><title>Test</title></head><body>Hello, World!</body></html>";

void WebTest(char *IP)
{
	SetupServer(IP);

sockaddr_in addrClient;
int iLength=sizeof(sockaddr_in);
SOCKET sClient=accept(sServer,(sockaddr *)&addrClient,&iLength);
char buf[2048];
int buflen;
buflen=recv(sClient,buf,2047,0);
if(buflen>0)
{
	buf[buflen]='\0';
	cout<<buf<<endl;
}
send(sClient,
	 longstr,
	 sizeof(longstr),0);
	
	closesocket(sClient);
	closesocket(sServer);
	WSACleanup();
}

int main(int argc, char* argv[])
{
	int ret=EOF;

	// load data base
	LoadDataBase();
	// initial server
	SetupServer(argv[1]);
	while(true)
	{
		// get request line
		// analyse and response
	}

	return ret;
}
