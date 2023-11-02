#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct sockaddr_in serv_addr;
int  r, r1, w, w1, c_sock_desc, choice;
unsigned short serv_port = 5040 ; 
char serv_ip[] = "192.168.24.20";

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
	
	
	while (1)
	{
		char sbuff[128], sbuff1[128], rbuff[256], rbuff1[256];
		printf("Enter keyword to search: ");
		gets(sbuff);
		
		w = sendto(c_sock_desc, sbuff, 128, 0, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
		if(w < 0)
		{
			printf("\nCLIENT ERROR : Cannot send message to the client.\n");
			close(c_sock_desc);
			exit(1);
		}
		
		int serv_len=sizeof(serv_addr);
		r = recvfrom(c_sock_desc, rbuff, 256, 0, (struct sockaddr*)&serv_addr, &serv_len);
		if(r < 0)
			printf("\nCLIENT ERROR : Cannot receive result from the server.\n");
		else
		{
			rbuff[r] = '\0';
			printf("\nCLIENT : SERVER MESSAGE:  \n%s\n", rbuff);
		}
		
		printf("Enter exact file name : ");
		gets(sbuff1);
		
		w1 = sendto(c_sock_desc, sbuff1, 128, 0, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
		if(w < 0)
		{
			printf("\nCLIENT ERROR : Cannot send message to the client.\n");
			close(c_sock_desc);
			exit(1);
		}
		
		int serv_len1=sizeof(serv_addr);
		r1 = recvfrom(c_sock_desc, rbuff1, 256, 0, (struct sockaddr*)&serv_addr, &serv_len1);
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
