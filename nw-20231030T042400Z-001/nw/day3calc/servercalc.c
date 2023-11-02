#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>

struct sockaddr_in server_address, client_address;
int sock_desc, accept_desc, r1, r2, r3, w, client_address_len, i_op1, i_op2, result=8;
unsigned short serv_port=5800;
char serv_ip[]="192.168.24.17";
char op1[128], op2[128], operand[128], s_result[128];

int main()
{
	sock_desc = socket (AF_INET, SOCK_STREAM, 0);
	if (sock_desc < 0)
	{
		printf("SERVER: Cannot create socket");
		exit(1);
	}
	
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(serv_port);
	inet_aton(serv_ip, (&server_address.sin_addr));
	
	int bind_func=bind(sock_desc, (struct sockaddr*)&server_address, sizeof(server_address));
	if (bind_func < 0)
	{
		printf("SERVER: Cannot bind.");
		close(sock_desc);
		exit(1);
	}

	while (1)
	{
		int listen_func = listen(sock_desc,1);
		if (listen_func < 0)
		{
			printf("\nSERVER ERROR: Cannot listen.\n");
			close(sock_desc);
			exit(1);
		}
		
		client_address_len = sizeof(client_address);
	
		printf("\nSERVER : Listening for clients... press ctrl + c to stop server :\n");
		accept_desc = accept(sock_desc, (struct sockaddr*)&client_address, &client_address_len);
		if(accept_desc  < 0)
		{
			printf("\nSERVER ERROR : Cannot accept client connection.\n");
			close(sock_desc);
			exit(1);
		}
		printf("\nSERVER : Connection from client %s accepted.\n", inet_ntoa(client_address.sin_addr));
		
		
		r1 = read(accept_desc, op1, 128);
		if(r1 < 0)
			printf("\nSERVER ERROR : Cannot receive operator1 from the client.\n");
		else
		{
			op1[r1]='/0';
			i_op1=atoi(op1);
		}
		r2 = read(accept_desc, op2, 128);
		if(r2 < 0)
			printf("\nSERVER ERROR : Cannot receive operator2 from the client.\n");
		else
		{
			op2[r2]='/0';
			i_op2=atoi(op2);
		}
		
		r3 = read(accept_desc, operand, 128);
		if(r3 < 0)
			printf("\nSERVER ERROR : Cannot receive operand from the client.\n");
		else
			operand[r1]='/0';
		
		printf("OP : %c", operand[0]);
		switch(operand[0])
		{
			case '+':
				result= i_op1 + i_op2;
				break;
			case '-':
				result= i_op1 - i_op2;
				break;
			case '*':
				result= i_op1 * i_op2;
				break;
			case '/':
				result= i_op1 / i_op2;
				break;
			default:
				printf("\nInvalid Operand.\n");
		}
		sprintf(s_result, "%d", result);
		w = write(accept_desc, s_result, 128);
		if(w < 0)
			printf("\nSERVER ERROR : Cannot send message to the client.\n");
		else
			printf("\nSERVER : Sent %s to client.\n",s_result);
	}
}
