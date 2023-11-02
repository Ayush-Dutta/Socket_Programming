#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct sockaddr_in servstruct, clientstruct;
int listenfd, bindconn, client_len, recvconn, recvconn1, sendconn, sendconn1, sendconn2;
unsigned int port = 6667;
char ip[] = "127.0.0.1";
char name[2048], name1[2048], name2[2048], content[2048], buff[2048], buff1[2048], buff2[2048], buff3[2048], buff4[2048], find[2048], ll1[2048], reply[2048];
FILE *fp, *fp1, *fp2;

int main()
{
	listenfd = socket(AF_INET, SOCK_DGRAM, 0);
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
	client_len = sizeof(clientstruct);
        recvconn = recvfrom(listenfd, name, sizeof(name), 0, (struct sockaddr*)&clientstruct, &client_len);
        if (recvconn < 0)
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
                sendconn = sendto(listenfd, content, sizeof(content), 0, (struct sockaddr*)&clientstruct, client_len);
                if (sendconn < 0)
                {
                        printf("\nSERVER ERROR: Cannot Write.\n");
		        close(listenfd);
		        exit(1);
                }
                recvconn1 = recvfrom(listenfd, name1, sizeof(name1), 0, (struct sockaddr*)&clientstruct, &client_len);
                if (recvconn1 < 0)
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
                        sendconn1 = sendto(listenfd, reply, sizeof(reply), 0, (struct sockaddr*)&clientstruct, client_len);
                        if (sendconn1 < 0)
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
                        sendconn2 = sendto(listenfd, buff4, sizeof(buff4), 0, (struct sockaddr*)&clientstruct, client_len);
                        if (sendconn2 < 0)
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
