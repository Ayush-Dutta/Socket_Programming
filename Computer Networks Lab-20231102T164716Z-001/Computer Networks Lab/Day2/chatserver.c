#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>

struct sockaddr_in servstruct,clientstruct;
int listenfd,bindconn,cli_len,acceptconn,listenconn,readconn,writeconn;
unsigned int port=6667;
char ip[]="127.0.0.1";
char message[128],buff[128];

int main(){
	listenfd=socket(AF_INET,SOCK_STREAM,0);
	if(listenfd<0){
		printf("\nServer Error. Cannot create socket\n");
		exit(1);
	}
	servstruct.sin_family=AF_INET;
	servstruct.sin_port=htons(port);
	inet_aton(ip,(&servstruct.sin_addr));
	bindconn=bind(listenfd,(struct sockaddr*) &servstruct,sizeof(servstruct));
	if(bindconn<0){
		printf("\nServer Error. Cannot bind.\n");
		close(listenfd);
		exit(1);
	}
	listenconn=listen(listenfd,5);
	if(listenconn<0){
		printf("\nServer Error. Cannot Listen\n");
		close(listenfd);
		exit(1);
	}
	cli_len=sizeof(clientstruct);
	acceptconn=accept(listenfd,(struct sockaddr*)&clientstruct,&cli_len);
	if(acceptconn<0){
		printf("\nServer Error. Cannot accept.\n");
		close(listenfd);
		exit(1);
	}
	do{
		readconn=read(acceptconn,buff,128);
		if(readconn<0){
			printf("\nServer Error. Cannot read\n");
			close(listenfd);
			exit(1);
		}
		else{
			printf("\n%s\n",buff);
			printf("\nEnter your message (Bye to exit)\n");
			gets(message);
			writeconn=write(acceptconn,message,128);
			if(writeconn<0){
				printf("\nServer Error. Cannot write\n");
				close(listenfd);
				exit(1);
			}
		}
	}while(1);
	close(listenfd);
	return 0;
}
