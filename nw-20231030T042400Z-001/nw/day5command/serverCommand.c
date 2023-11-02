#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <string.h>

struct sockaddr_in server_address, client_address;
int sock_desc, accept_desc, r, w, client_address_len;
unsigned short serv_port=5060;
char serv_ip[]="127.0.0.1";

int main()
{
	sock_desc=socket(AF_INET, SOCK_STREAM, 0);
	if(sock_desc < 0)
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
		int listen_func = listen(sock_desc,5);
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
		while (1)
		{
			char rbuff[4096]="", linebuff[1024]="";
			r = read(accept_desc, rbuff, 4096);
			if(r < 0)
				printf("\nSERVER ERROR : Cannot receive command from the client.\n");
			else
				rbuff[r]='\0';
				
			char sbuff[4096]="";
			int commandStatus=system(rbuff);
			if (commandStatus != 0)
				strcat(sbuff,"Command not found");
			else
			{
				strcat(rbuff, ">output");
				system(rbuff);
			}
			FILE *fp;
			fp=fopen("output","r");
			
			if (fp ==NULL)
				printf("Cannot read file\n");
			
			
			while (fgets(linebuff, 1024, fp))
				strcat(sbuff, linebuff);
			
			fclose(fp);
			
			w = write(accept_desc, sbuff, 1024);
			if(w < 0)
				printf("\nSERVER ERROR : Cannot sbuff message to the client.\n");
			
			system("rm output");
		}
	}
}









