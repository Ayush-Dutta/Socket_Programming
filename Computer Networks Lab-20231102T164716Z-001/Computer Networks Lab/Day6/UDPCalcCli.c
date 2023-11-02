#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>

struct sockaddr_in servstruct, clientstruct;
int listenfd_cli, sendconn1, sendconn2, sendconn3, recvconn, serv_len;
unsigned int port = 8000;
char ip[] = "127.0.0.1";
char num1[128], num2[128], operator[2], output[128];

int main()
{
	listenfd_cli = socket(AF_INET, SOCK_DGRAM, 0);
	if (listenfd_cli < 0)
	{
		printf("\nClient Error: Cannot create socket.\n");
		close(listenfd_cli);
		exit(1);
	}
	servstruct.sin_family = AF_INET;
	servstruct.sin_port = htons(port);
	inet_aton(ip,(&servstruct.sin_addr));
	printf("\nEnter the first num second number and the operator\n");
	gets(num1);
	gets(num2);
	gets(operator);
	serv_len = sizeof(servstruct);
	sendconn1 = sendto(listenfd_cli, num1, sizeof(num1), 0, (struct sockaddr*)&servstruct, serv_len);
	sendconn2 = sendto(listenfd_cli, num2, sizeof(num2), 0, (struct sockaddr*)&servstruct, serv_len);
	sendconn3 = sendto(listenfd_cli, operator, sizeof(operator), 0, (struct sockaddr*)&servstruct, serv_len);
	if (sendconn1 < 0 || sendconn2 < 0 || sendconn3 < 0)
	{
			printf("\nClient Error: Cannot Send.\n");
			close(listenfd_cli);
			exit(1);
	}
	recvconn = recvfrom(listenfd_cli, output, sizeof(output), 0, (struct sockaddr*)&servstruct, &serv_len);
	if (recvconn < 0)
	{
		printf("\nClient Error: Cannot Receive.\n");
		close(listenfd_cli);
		exit(1);
	}
	printf("\nThe output is %s\n",output);
	close(listenfd_cli);
	return 0;
}
