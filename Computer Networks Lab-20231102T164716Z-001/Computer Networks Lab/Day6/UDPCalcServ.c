#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>

struct sockaddr_in servstruct, clientstruct;
int listenfd, bindconn, client_len, recvconn1, recvconn2, recvconn3, sendconn;
unsigned int port = 8000;
char ip[] = "127.0.0.1";
char num1[128], num2[128], operator[2], output[128];
int a, b, out;

int main()
{
	listenfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (listenfd < 0)
	{
		printf("\nServer Error: Cannot create socket.\n");
		exit(1);
	}
	servstruct.sin_family = AF_INET;
	servstruct.sin_port = htons(port);
	inet_aton(ip,(&servstruct.sin_addr));
	bindconn = bind(listenfd, (struct sockaddr*) &servstruct, sizeof(servstruct));
	if (bindconn < 0)
	{
		printf("\nServer Error: Cannot Bind.\n");
		close(listenfd);
		exit(1);
	}
	client_len = sizeof(clientstruct);
	recvconn1 = recvfrom(listenfd, num1, sizeof(num1), 0, (struct sockaddr*)&clientstruct, &client_len);
	recvconn2 = recvfrom(listenfd, num2, sizeof(num2), 0, (struct sockaddr*)&clientstruct, &client_len);
	recvconn3 = recvfrom(listenfd, operator, sizeof(operator), 0, (struct sockaddr*)&clientstruct, &client_len);
	if (recvconn1 < 0 || recvconn2 < 0 || recvconn3 < 0)
	{
			printf("\nServer Error: Cannot Receive.\n");
			close(listenfd);
			exit(1);
	}
	else
	{
			a = atoi(num1);
			b = atoi(num2);
			if (operator[0] == '+')
				out = a + b;
			else if (operator[0] == '-')
				out = a - b;
			else if (operator[0] == '*')
				out = a * b;
			else if (operator[0] == '/' && b != '0')
				out = a / b;
			else
				printf("\nWrong Operator.\n");
			sprintf(output, "%d", out);
			printf("\nOperation Successful.\n");
			sendconn = sendto(listenfd, output, sizeof(output), 0, (struct sockaddr*)&clientstruct, client_len);
			if(sendconn < 0)
			{
				printf("\nServer Error: Cannot Send.\n");
				close(listenfd);
				exit(1);
			}
	}
	close(listenfd);
	return 0;
}
