#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct sockaddr_in serv_addr;
int  r, w1, w2, w3, c_sock_desc;
unsigned short serv_port = 5900 ; 
char serv_ip[] = "192.168.24.20";
char op1[128], op2[128], operand[128], s_result[128];

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

	r = read(c_sock_desc, s_result,128);
	if(r < 0)
		printf("\nCLIENT ERROR : Cannot receive result from the server.\n");
	else
	{
		s_result[r] = '\0';
		printf("\nCLIENT : SERVER MESSAGE:  %s\n", s_result);
	}
	close(c_sock_desc);
	exit(1);
}
