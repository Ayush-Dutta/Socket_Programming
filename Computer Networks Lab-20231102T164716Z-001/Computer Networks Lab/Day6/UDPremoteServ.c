#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct sockaddr_in servstruct, clientstruct;
int listenfd, bindconn, client_len, recvconn, sendconn;
unsigned int port = 6768;
char ip[]="127.0.0.1";
char buff1[256], buff2[256], buff3[256];
FILE *fp;

int main()
{
	listenfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (listenfd < 0)
	{
		printf("\nSERVER ERROR: Scoket Creation Failed.\n");
		exit(1);
	}
	servstruct.sin_family = AF_INET;
	servstruct.sin_port = htons(port);
	inet_aton(ip, (&servstruct.sin_addr));
	bindconn = bind(listenfd, (struct sockaddr*)&servstruct, sizeof(servstruct));
	if (bindconn < 0)
	{
		printf("\nSERVER ERROR: Cannot Bind.\n");
		close(listenfd);
		exit(1);
	}
	while(1)
	{
		client_len = sizeof(clientstruct);
		recvconn = recvfrom(listenfd, buff1, sizeof(buff1), 0, (struct sockaddr*)&clientstruct, &client_len);
		if (recvconn < 0)
		{
			printf("\nSERVER ERROR: Cannot Receive.\n");
			close(listenfd);
			exit(1);
		}
		else
		{
			if (strcmp(buff1, "END")!=0)
			{
				strcat(buff1," > xyz");
				system(buff1);
				fp = fopen("xyz","a+");
				while(fgets(buff2,256,fp)!=NULL)
					strcat(buff3, buff2);
			}
			printf("\nSUCCESSFUL!\n");
			sendconn = sendto(listenfd, buff3, sizeof(buff3), 0, (struct sockaddr*)&clientstruct, client_len);
			if (sendconn < 0)
			{
				printf("\nSERVER ERROR: Cannot Send.\n");
				close(listenfd);
				exit(1);
			}
			buff2[0]='\0';
			buff3[0]='\0';
		}	
	}
	close(listenfd);
	return 0;
}
