#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <string.h>

struct sockaddr_in server_address, client_address;
int sock_desc, accept_desc, r, r1, w, w1, client_address_len;
unsigned short serv_port=5020;
char serv_ip[]="192.168.24.20";

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
			char rbuff[128]="", rbuff1[128]="", linebuff[1024]="";
			r = read(accept_desc, rbuff, 128);
			if(r < 0)
			{
				printf("\nSERVER ERROR : Cannot receive command from the client.\n");
				break;
			}
			else
				rbuff[r]='\0';
				
			char sbuff[65536]="", sbuff1[65536]="", command[1024]="find ", name1[128]="", name2[128]="", ll1[256]="ls -l ", reply[256]="", buff1[2048]="", buff2[2048]="", buff3[2048]="";
			strcat(command, rbuff);
			strcat(command, "*>output");
			system(command);
			
			
			FILE *fp, *fp1, *fp2;
			fp=fopen("output","r");
			
			
			while (fgets(linebuff, 1024, fp))
				strcat(sbuff, linebuff);
			
			fclose(fp);

			system("rm output");
			
			w = write(accept_desc, sbuff, 65536);
			if(w < 0)
				printf("\nSERVER ERROR : Cannot send message to the client.\n");
				
			
			r1 = read(accept_desc, name1, 128);
			if(r1 < 0)
			{
				printf("\nSERVER ERROR : Cannot receive command from the client.\n");
				break;
			}
			
				
			
			 strcpy(name2, name1);
	                strcat(name1,"> filename");
	                strcat(ll1, name1);
	                system(ll1);
	                fp1 = fopen("filename","r");
	                while (fgets(buff1, 2048, fp1)!=NULL)
	                        strcat(buff2, buff1);
	                fclose(fp1);
	                
	                if (buff2[3]=='x')
	                        strcpy(sbuff1,"Executable File, can't be read.");
	                else
	                {
	                        fp2 = fopen(name2,"r");
	                        while (fgets(buff3, 2048, fp2)!=NULL)
	                                strcat(sbuff1, buff3);
	                        fclose(fp2);
	                }
	                w1 = write(accept_desc, sbuff1, 65536);
                        if (w1 < 0)
                        {
                                printf("\nSERVER ERROR: Cannot Write.\n");
		                close(sock_desc);
		                exit(1);
                        }
        
		}
	}
}









