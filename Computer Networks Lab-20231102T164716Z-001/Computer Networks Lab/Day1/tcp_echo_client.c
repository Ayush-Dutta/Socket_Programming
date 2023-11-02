#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>

struct sockaddr_in servstruct, clientstruct;
int listenfd_cli, connectconn, cli_len, writeconn, readconn;
unsigned int port = 6667;
char ip[] = "127.0.0.1";
char buffer_cl[128] = "Proteen", buff[128];

int main()
{

	listenfd_cli = socket(AF_INET, SOCK_STREAM, 0);
	if(listenfd_cli < 0)
	{
		printf("\nCLIENT ERROR: Socket Creation failed.\n");
		exit(1);
	}
	servstruct.sin_family = AF_INET;
	servstruct.sin_port = htons(port);
	inet_aton(ip, (&servstruct.sin_addr));
	connectconn = connect(listenfd_cli, (struct sockaddr*)&servstruct, sizeof(servstruct));
	if(connectconn < 0)
	{
		printf("\nCLIENT ERROR: Cannot connect.\n");
		close(listenfd_cli);
		exit(1);
	}
	writeconn = write(listenfd_cli, buffer_cl, 128);
	if(writeconn < 0)
	{
		printf("\nCLIENT ERROR: Cannot write.\n");
		close(listenfd_cli);
		exit(1);
	}
	readconn = read(listenfd_cli,buff,128);
	if(readconn < 0)
	{
		printf("\nCLIENT ERROR: Cannot read.\n");
		close(listenfd_cli);
		exit(1);
	}
	else
		printf("\nEchoed Back: %s\n",buff);
	close(listenfd_cli);
	return 0;
}