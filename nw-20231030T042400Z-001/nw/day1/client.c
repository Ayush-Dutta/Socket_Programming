#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct sockaddr_in serv_addr;
int  r, w, skfd;
unsigned short serv_port = 5500 ; 
char serv_ip[] = "192.168.24.17";
char rbuff[128];
char sbuff[128];

int main()
{
	skfd = socket(AF_INET, SOCK_STREAM, 0);
	if(skfd < 0)
	{
		printf("\nCLIENT ERROR : Cannot create socket.\n");
		exit(1);
	}
	
	//bzero(&serv_addr, sizeof(serv_addr));
	
	serv_addr.sin_family = AF_INET;		//address family
	serv_addr.sin_port = htons(serv_port);	//port number
	inet_aton(serv_ip, (&serv_addr.sin_addr));	//ip address
	printf("\nTCP ECHO CLIENT.\n");
	
	int connect_func= connect(skfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	if(connect_func < 0)
	{
		printf("\nCLIENT ERROR : Cannot connect to the server.\n");
		close(skfd);
		exit(1);
	}
	
	printf("\nCLIENT : Connected to the server.\nEnter message : ");
	gets(sbuff);
	
	w = write(skfd, sbuff, 128);
	if(w < 0)
	{
		printf("\nCLIENT ERROR : Cannot send message to the client.\n");
		close(skfd);
		exit(1);
	}
	
	printf("\nCLIENT : Message sent to echo server.\n");
	r = read(skfd, rbuff, 128);
	if(r < 0)
		printf("\nCLIENT ERROR : Cannot receive message from the client.\n");
	else
	{
		rbuff[r] = '\0';
		printf("\nCLIENT : Message sent to echo server: %s\n", rbuff);
	}
	close(skfd);
	exit(1);
}
