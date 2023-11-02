#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct sockaddr_in servstruct, clientstruct;
int listenfd, bindconn, acceptconn, listenconn, client_len, readconn, readconn1, writeconn, writeconn1, writeconn2;
unsigned int port = 6667;
char ip[] = "127.0.0.1";
char name[2048], name1[2048], name2[2048], content[2048], buff[2048], buff1[2048], buff2[2048], buff3[2048], buff4[2048], find[2048], ll1[2048], reply[2048];
FILE *fp, *fp1, *fp2;

int main()
{
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if (listenfd < 0)
	{
		printf("\nSERVER ERROR: Scoket Creation Failed.\n");
		exit(1);
	}
	else
	        printf("\nSERVER SUCCESS: Socket Creation.\n");
	servstruct.sin_family = AF_INET;
	servstruct.sin_port = htons(port);
	inet_aton(ip, (&servstruct.sin_addr));
	bindconn = bind(listenfd, (struct sockaddr*)&servstruct, sizeof(servstruct));
	if (bindconn < 0)
	{
		printf("\nSERVER ERROR: Cannot Bind.\n");
		close(listenfd);
		exit(1);
	}
	else
	        printf("\nSERVER SUCCESS: Bind.\n");
	listenconn = listen(listenfd, 5);
	if (listenconn < 0)
	{
		printf("\nSERVER ERROR: Cannot Listen.\n");
		close(listenfd);
		exit(1);
	}
	else
	        printf("\nSERVER SUCCESS: Listen.\n");
	client_len = sizeof(clientstruct);
	acceptconn = accept(listenfd, (struct sockaddr*)&clientstruct, &client_len);
	if (acceptconn < 0)
	{
		printf("\nSERVER ERROR: Cannot Accept.\n");
		close(listenfd);
		exit(1);
	}
	else
	        printf("\nSERVER SUCCESS: Accept.\n");
        readconn = read(acceptconn, name, 2048);
        if (readconn < 0)
        {
                printf("\nSERVER ERROR: Cannot Read.\n");
		close(listenfd);
		exit(1);
        }
        else
        {
                strcpy(find,"find ");
                strcat(name,"* > list");
                strcat(find, name);
                system(find);
                fp = fopen("list","a+");
                while (fgets(buff, 2048, fp)!=NULL)
                        strcat(content, buff);
                writeconn = write(acceptconn, content, 2048);
                if (writeconn < 0)
                {
                        printf("\nSERVER ERROR: Cannot Write.\n");
		        close(listenfd);
		        exit(1);
                }
                readconn1 = read(acceptconn, name1, 2048);
                if (readconn1 < 0)
                {
                        printf("\nSERVER ERROR: Cannot Read.\n");
		        close(listenfd);
		        exit(1);
                }
                strcpy(name2, name1);
                strcat(name1,"> filename");
                strcpy(ll1,"ls -l ");
                strcat(ll1, name1);
                system(ll1);
                fp1 = fopen("filename","r");
                while (fgets(buff1, 2048, fp1)!=NULL)
                        strcat(buff2, buff1);
                if (buff2[3]=='x')
                {
                        strcpy(reply,"Executable File, can't be read.");
                        writeconn1 = write(acceptconn, reply, 2048);
                        if (writeconn1 < 0)
                        {
                                printf("\nSERVER ERROR: Cannot Write.\n");
		                close(listenfd);
		                exit(1);
                        }
                }
                else
                {
                        fp2 = fopen(name2,"r");
                        while (fgets(buff3, 2048, fp2)!=NULL)
                                strcat(buff4, buff3);
                        writeconn2 = write(acceptconn, buff4, 2048);
                        if (writeconn2 < 0)
                        {
                                printf("\nSERVER ERROR: Cannot Write.\n");
		                close(listenfd);
		                exit(1);
                        }
                }
        }
        close(listenfd);
        return 0;
}
