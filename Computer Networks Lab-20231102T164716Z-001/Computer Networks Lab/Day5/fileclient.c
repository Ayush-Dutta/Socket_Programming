#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct sockaddr_in servstruct, clientstruct;
int listenfd_cli, connect_conn, write_conn, write_conn1, read_conn, read_conn1, read_conn2;
unsigned int port = 6667;
char ip[] = "127.0.0.1";
char buff1[2048], buff2[2048], buff3[2048], buff4[2048], buff5[2048];

int main()
{
	listenfd_cli = socket(AF_INET, SOCK_STREAM, 0);
	if (listenfd_cli < 0)
	{
		printf("\nCLIENT ERROR: Cannot create socket.\n");
		exit(1);
	}
	servstruct.sin_family = AF_INET;
	servstruct.sin_port = htons(port);
	inet_aton(ip, (&servstruct.sin_addr));
	connect_conn = connect(listenfd_cli, (struct sockaddr *) &servstruct, sizeof(servstruct));
	if (connect_conn < 0)
	{
		printf("\nCLIENT ERROR: Cannot connect.\n");
		close(listenfd_cli);
		exit(1);
	}
	//while(1)
	//{
		printf("\nEnter a file name/substring:\n");
		gets(buff1);
		write_conn = write(listenfd_cli, buff1, 2048);
		if (write_conn < 0)
		{
			printf("\nCLIENT ERROR: Cannot write.\n");
			close(listenfd_cli);
			exit(1);
		}
		read_conn = read(listenfd_cli, buff2, 2048);
		if (read_conn < 0)
		{
			printf("\nCLIENT ERROR: Cannot read.\n");
			close(listenfd_cli);
			exit(1);
		}
		else
			printf("\n%s\n",buff2);
		printf("\nEnter a specific file name/substring:\n");
		gets(buff3);
		write_conn1 = write(listenfd_cli, buff3, 2048);
		if (write_conn1 < 0)
		{
			printf("\nCLIENT ERROR: Cannot write.\n");
			close(listenfd_cli);
			exit(1);
		}
                read_conn1 = read(listenfd_cli, buff4, 2048);
		if (read_conn1 < 0)
		{
			printf("\nCLIENT ERROR: Cannot read.\n");
			close(listenfd_cli);
			exit(1);
		}
		else
			printf("\n%s\n",buff4);
	//}
	close(listenfd_cli);
	return 0;
}

