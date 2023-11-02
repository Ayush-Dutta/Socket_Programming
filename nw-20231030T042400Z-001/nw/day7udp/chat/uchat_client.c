#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct sockaddr_in serv_addr;
int  r, w, c_sock_desc;
unsigned short serv_port = 5506 ; 
char serv_ip[] = "127.0.0.1";

int main()
{
	c_sock_desc = socket(AF_INET, SOCK_DGRAM, 0);
	if(c_sock_desc < 0)
	{
		printf("\nCLIENT ERROR : Cannot create socket.\n");
		exit(1);
	}
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(serv_port);
	inet_aton(serv_ip, (&serv_addr.sin_addr));
	
/*	int connect_func= connect(c_sock_desc, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	if(connect_func < 0)
	{
		printf("\nCLIENT ERROR : Cannot connect to the server.\n");
		close(c_sock_desc);
		exit(1);
	}*/
	printf("\nCLIENT : Connected to the server.\n");
	for ( ; ; )
	{
		char rbuff[128], sbuff[128];
		printf("\nEnter message : ");
		gets(sbuff);
		sendto(c_sock_desc, sbuff, 128, 0, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
		printf("\nCLIENT : Message sent to server: %s.\n",sbuff);
		int serv_len=sizeof(serv_addr);
		recvfrom(c_sock_desc, rbuff, 128, 0, (struct sockaddr*)&serv_addr, &serv_len);
		printf("\nCLIENT : SERVER MESSAGE: %s\n", rbuff);
		
	/*	w = write(c_sock_desc, sbuff, 128);
		if(w < 0)
		{
			printf("\nCLIENT ERROR : Cannot send message to the client.\n");
			close(c_sock_desc);
			exit(1);
		}
		
		printf("\nCLIENT : Message sent to server: %s.\n",sbuff);
		r = read(c_sock_desc, rbuff, 128);
		if(r < 0)
			printf("\nCLIENT ERROR : Cannot receive message from the client.\n");
		else
		{
			rbuff[r] = '\0';
			printf("\nCLIENT : SERVER MESSAGE: %s\n", rbuff);
		}*/
	}
	close(c_sock_desc);
	exit(1);
}
