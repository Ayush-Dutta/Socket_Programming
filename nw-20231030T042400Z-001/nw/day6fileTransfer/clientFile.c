#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct sockaddr_in serv_addr;
int  r, r1, w, w1, c_sock_desc, choice;
unsigned short serv_port = 5020 ; 
char serv_ip[] = "192.168.24.20";

int main()
{
	c_sock_desc = socket(AF_INET, SOCK_STREAM, 0);
	if(c_sock_desc < 0)
	{
		printf("\nCLIENT ERROR : Cannot create socket.\n");
		exit(1);
	}
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(serv_port);
	inet_aton(serv_ip, (&serv_addr.sin_addr));
	
	int connect_func= connect(c_sock_desc, (struct sockaddr*)&serv_addr, sizeof(serv_addr));	
	if(connect_func < 0)
	{
		printf("\nCLIENT ERROR : Cannot connect to the server.\n");
		close(c_sock_desc);
		exit(1);
	}
	printf("\nCLIENT : Connected to the server.\n");
	while (1)
	{
		char sbuff[128], sbuff1[128], rbuff[65536], rbuff1[65536];
		printf("Enter keyword to search: ");
		gets(sbuff);
		
		w = write(c_sock_desc, sbuff, 128);
		if(w < 0)
		{
			printf("\nCLIENT ERROR : Cannot send message to the client.\n");
			close(c_sock_desc);
			exit(1);
		}
		
		r = read(c_sock_desc, rbuff,65536);
		if(r < 0)
			printf("\nCLIENT ERROR : Cannot receive result from the server.\n");
		else
		{
			rbuff[r] = '\0';
			printf("\nCLIENT : SERVER MESSAGE:  \n%s\n", rbuff);
		}
		
		printf("Enter exact file name : ");
		gets(sbuff1);
		
		w1 = write(c_sock_desc, sbuff1, 128);
		if(w < 0)
		{
			printf("\nCLIENT ERROR : Cannot send message to the client.\n");
			close(c_sock_desc);
			exit(1);
		}
		
		r1 = read(c_sock_desc, rbuff1,65536);
		if(r1 < 0)
			printf("\nCLIENT ERROR : Cannot receive result from the server.\n");
		else
		{
			rbuff1[r1] = '\0';
			printf("\nCLIENT : SERVER MESSAGE:  \n%s\n", rbuff1);
		}
		

		FILE *file;
		file = fopen("serverMessage.txt", "w");
		fprintf(file, "%s", rbuff1);
		fclose(file);
		
	}
	close(c_sock_desc);
	exit(1);
}
