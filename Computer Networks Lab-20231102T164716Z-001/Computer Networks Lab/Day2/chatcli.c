#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>

struct sockaddr_in servstruct,clientstruct;
int listenfd_cli,connectconn,writeconn,readconn;
unsigned int port=6667;
char ip[]="127.0.0.1";
char message[128],buff[128];

int main(){
	listenfd_cli=socket(AF_INET,SOCK_STREAM,0);
	if(listenfd_cli<0){
		printf("\nClient Error. Cannot create socket\n");
		close(listenfd_cli);
		exit(1);
	}
	servstruct.sin_family=AF_INET;
	servstruct.sin_port=htons(port);
	inet_aton(ip,(&servstruct.sin_addr));
	connectconn=connect(listenfd_cli,(struct sockaddr*) &servstruct,sizeof(servstruct));
	if(connectconn<0){
		printf("\nCLIENT ERROR:Cannot connect to the server.\n");
		close(listenfd_cli);
		exit(1);
	}
	do{
		printf("\nEnter the message (Bye to exit)\n");
		gets(message);
		writeconn=write(listenfd_cli,message,128);
		if(writeconn<0){
			printf("\nClient Error. Cannot write\n");
			close(listenfd_cli);
			exit(1);
		}
		if(strcmp(message,"Bye")==0){
			break;
		}
		readconn=read(listenfd_cli,buff,128);
		if(readconn<0){
			printf("\nCLIENT ERROR: Cannot receive message from the server.\n");
			close(listenfd_cli);
			exit(1);
		}
		else{
			printf("\n%s\n",buff);
			if(strcmp(buff,"Bye")==0)
				break;
		}
		
	}while(1);
	close(listenfd_cli);
	return 0;
}
