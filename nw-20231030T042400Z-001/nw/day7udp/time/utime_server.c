#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <time.h>

struct sockaddr_in server_address, client_address;
int sock_desc, accept_desc, r, w, client_address_len, i_hour;
unsigned short serv_port=6000;
char serv_ip[]="192.168.24.20";
char op1[128], s_result[128], hour [128];

int main()
{
	sock_desc = socket (AF_INET, SOCK_DGRAM, 0);
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
		client_address_len = sizeof(client_address);
	
		printf("\nSERVER : Listening for clients... press ctrl + c to stop server :\n");
		recvfrom(sock_desc, op1, 128, 0, (struct sockaddr*)&client_address, &client_address_len);
		
		
		
		
		time_t curr_time_s = time(NULL);
		snprintf(s_result, 128, "%s", ctime(&curr_time_s));
		hour[0]=s_result[11];
		hour[1]=s_result[12];
		hour[2]='\0';
		i_hour=atoi(hour);
		
		if (i_hour<12)
			strcat(s_result, "\n\tGood Morning!! ");
		else if  (i_hour>11 && i_hour <17)
			strcat(s_result, "\n\tGood Afternoon!! ");
		else if  (i_hour>=17 && i_hour <21)
			strcat(s_result, "\n\tGood Evening!! ");
		else
			strcat(s_result, "\n\tGood Night!! ");
		//sprintf(s_result, "%ld", curr_time_s);
		w = sendto(sock_desc, s_result, 128, 0, (struct sockaddr*)&client_address, client_address_len);
		if(w < 0)
			printf("\nSERVER ERROR : Cannot send message to the client.\n");
		else
			printf("\nSERVER : Sent %s to client.\n",s_result);
	}
}




