#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
struct sockaddr_in servstruct,clientstruct;
int listenfd_cli,connect_call,write_call,read_call;
unsigned int portno=6001;
char ip_add[]="127.0.0.1";
char num[128],output[128];
int main(){
	listenfd_cli=socket(AF_INET,SOCK_STREAM,0);
	if(listenfd_cli<0){
		printf("\nClient Error. Cannot create socket\n");
		close(listenfd_cli);
		exit(1);
	}
	servstruct.sin_family=AF_INET;
	servstruct.sin_port=htons(portno);//htons->host to network shortform
	inet_aton(ip_add,(&servstruct.sin_addr));//aton->address to network
	connect_call=connect(listenfd_cli,(struct sockaddr*) &servstruct,sizeof(servstruct));
	if(connect_call<0){
		printf("\nCLIENT ERROR:Cannot connect to the server.\n");
		close(listenfd_cli);
		exit(1);
	}
	printf("\nEnter the expression\n");
	gets(num);
	write_call=write(listenfd_cli,num,128);
	if(write_call<0 ){
			printf("\nClient Error. Cannot write\n");
			close(listenfd_cli);
			exit(1);
	}
	read_call=read(listenfd_cli,output,128);
	if(read_call<0){
		printf("\nClient Error. Cannot read\n");
		close(listenfd_cli);
		exit(1);
	}
	printf("\nThe output is %s\n",output);
	close(listenfd_cli);
	return 0;
}
