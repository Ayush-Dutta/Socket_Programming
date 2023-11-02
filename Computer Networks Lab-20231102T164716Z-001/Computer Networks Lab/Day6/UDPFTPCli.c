#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct sockaddr_in servstruct, clientstruct;
int listenfd_cli, sendconn, sendconn1, recvconn, recvconn1, serv_len;
unsigned int port = 6667;
char ip[] = "127.0.0.1";
char buff1[2048], buff2[2048], buff3[2048], buff4[2048], buff5[2048];

int main()
{
	listenfd_cli = socket(AF_INET, SOCK_DGRAM, 0);
	if (listenfd_cli < 0)
	{
		printf("\nCLIENT ERROR: Cannot create socket.\n");
		exit(1);
	}
	servstruct.sin_family = AF_INET;
	servstruct.sin_port = htons(port);
	inet_aton(ip, (&servstruct.sin_addr));
	serv_len = sizeof(servstruct);
	printf("\nEnter a file name/substring:\n");
	gets(buff1);
        sendconn = sendto(listenfd_cli, buff1, sizeof(buff1), 0, (struct sockaddr*)&servstruct, sizeof(servstruct));
	if (sendconn < 0)
	{
		printf("\nCLIENT ERROR: Cannot send.\n");
		close(listenfd_cli);
		exit(1);
	}
	recvconn = recvfrom(listenfd_cli, buff2, sizeof(buff2), 0, (struct sockaddr*)&servstruct, &serv_len);
	if (recvconn < 0)
	{
		printf("\nCLIENT ERROR: Cannot receive.\n");
		close(listenfd_cli);
		exit(1);
	}
	else
		printf("\n%s\n",buff2);
	printf("\nEnter a specific file name/substring:\n");
	gets(buff3);
	sendconn1 = sendto(listenfd_cli, buff3, sizeof(buff3), 0, (struct sockaddr*)&servstruct, sizeof(servstruct));
	if (sendconn1 < 0)
	{
		printf("\nCLIENT ERROR: Cannot send.\n");
		close(listenfd_cli);
		exit(1);
	}
        recvconn1 = recvfrom(listenfd_cli, buff4, sizeof(buff4), 0, (struct sockaddr*)&servstruct, &serv_len);
	if (recvconn1 < 0)
	{
		printf("\nCLIENT ERROR: Cannot receive.\n");
		close(listenfd_cli);
		exit(1);
	}
	else
		printf("\n%s\n",buff4);
	close(listenfd_cli);
	return 0;
}
