#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>

struct sockaddr_in server_address, client_address;
int sock_desc, accept_desc, r, w, client_address_len;
unsigned short serv_port= 5506;
char serv_ip[]="192.168.24.20";
char rbuff[128], sbuff[128];

int main()
{
	sock_desc = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock_desc < 0)
	{
		printf("SERVER: Cannot create socket.");
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
	
/*	int listen_func= listen(sock_desc, 5);
	if(listen_func < 0)
	{
		printf("\nSERVER ERROR : Cannot listen.\n");
		close(sock_desc);
		exit(1);
	}*/
	
	client_address_len = sizeof(client_address);
	
	printf("\nSERVER : Listening for clients... press ctrl + c to stop echo server :\n");
	for( ; ; )
	{
		char sbuff[128], rbuff[128];
	/*	accept_desc = accept(sock_desc, (struct sockaddr*)&client_address, &client_address_len);
		if(accept_desc  < 0)
		{
			printf("\nSERVER ERROR : Cannot accept client connection.\n");
			close(sock_desc);
			exit(1);
		}*/
		//printf("\nSERVER : Connection from client %s accepted.\n", inet_ntoa(client_address.sin_addr));
		
		int len=recvfrom(sock_desc, rbuff, 128, 0, (struct sockaddr*)&client_address, &client_address_len);
		printf("%d", len);
		printf("\nSERVER: CLIENT MESSSAGE: %s.\nSERVER: Enter message : ", rbuff);
		gets(sbuff);
		sendto(sock_desc, sbuff, 128, 0, (struct sockaddr*)&client_address, client_address_len);
		/*r = read(accept_desc, rbuff, 128);
		if(r < 0)
			printf("\nSERVER ERROR : Cannot receive message from the client.\n");
		else
		{
			rbuff[r] ='\0';
			
			printf("\nSERVER: CLIENT MESSSAGE: %s.\nSERVER: Enter message : ", rbuff);
			gets(sbuff);
			w = write(accept_desc, sbuff, 128);
			if(w < 0)
				printf("\nSERVER ERROR : Cannot send message to the client.\n");
		}*/
	}
}



























