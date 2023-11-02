#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
struct sockaddr_in servstruct,clientstruct;
int listenfd,bind_call,cli_len,accept_call,listen_call,read_call1,read_call2,read_call3,write_call;
unsigned int portno=8000;
char ip_add[]="127.0.0.1";
char num1[128],num2[128],operator[2],output[128];
int a,b,out;
int main(){
	
	listenfd=socket(AF_INET,SOCK_STREAM,0);
	if(listenfd<0){
		printf("\nServer Error. Cannot create socket\n");
		exit(1);
	}
	servstruct.sin_family=AF_INET;
	servstruct.sin_port=htons(portno);
	inet_aton(ip_add,(&servstruct.sin_addr));
	bind_call=bind(listenfd,(struct sockaddr*) &servstruct,sizeof(servstruct));
	if(bind_call<0){
		printf("\nServer Error. Cannot bind.\n");
		close(listenfd);
		exit(1);
	}
	listen_call=listen(listenfd,5);
	if(listen_call<0){
		printf("\nServer Error. Cannot Listen\n");
		close(listenfd);
		exit(1);
	}
	cli_len=sizeof(clientstruct);
	accept_call=accept(listenfd,(struct sockaddr*)&clientstruct,&cli_len);
	if(accept_call<0){
		printf("\nServer Error. Cannot accept.\n");
		close(listenfd);
		exit(1);
	}
	read_call1=read(accept_call,num1,128);
	read_call2=read(accept_call,num2,128);
	read_call3=read(accept_call,operator,2);
	if(read_call1<0 ||read_call2<0 || read_call3<0){
			printf("\nServer Error. Cannot read\n");
			close(listenfd);
			exit(1);
	}
	else{
			a=atoi(num1);
			b=atoi(num2);
			if(operator[0]=='+'){
				out=a+b;
			}
			else if(operator[0]=='-'){
				out=a-b;
			}
			else if(operator[0]=='*'){
				out=a*b;
			}
			else if(b!='0'){
				out=a/b;
			}
			else{
				printf("\nWrong Operator\n");
			}
			sprintf(output,"%d",out);
			printf("\nOperation successful\n");
			write_call=write(accept_call,output,128);
			if(write_call<0){
				printf("\nServer Error. Cannot write\n");
				close(listenfd);
				exit(1);
			}
	}
	close(listenfd);
	return 0;
}
