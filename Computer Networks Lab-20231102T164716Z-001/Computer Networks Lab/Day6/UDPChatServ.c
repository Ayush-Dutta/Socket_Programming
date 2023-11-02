#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct sockaddr_in servstruct, clientstruct;
int listenfd, bindconn, client_len, recvconn, sendconn;
unsigned int port = 6667;
char ip[] = "127.0.0.1";
char buff[128], msg[128];

int main()
{
      listenfd = socket(AF_INET, SOCK_DGRAM, 0);
      if (listenfd < 0)
      {
            printf("\n[-] SERVER ERROR: Socket Creation failed.\n");
            exit(1);
      }
      else
            printf("\n[+] SERVER SUCCESS: Socket Created.\n");
      servstruct.sin_family = AF_INET;
      servstruct.sin_port = htons(port);
      inet_aton(ip, (&servstruct.sin_addr));
      bindconn = bind(listenfd, (struct sockaddr*)&servstruct, sizeof(servstruct));
      if (bindconn < 0)
      {
            printf("\n[-] SERVER ERROR: Bind failed.\n");
            close(listenfd);
            exit(1);
      }
      else
            printf("\n[+] SERVER SUCCESS: Bind.\n");
      while(1)
      {
            client_len = sizeof(clientstruct);
            recvconn = recvfrom(listenfd, buff, sizeof(buff), 0, (struct sockaddr*)&clientstruct, &client_len);
            if (recvconn < 0)
            {
                  printf("\n[-] SERVER ERROR: Receive failed.\n");
                  close(listenfd);
                  exit(1);
            }
            else
            {
                  printf("\n[+] SERVER SUCCESS: Receive.\n");
                  printf("\n%s\n",buff);
                  printf("\nEnter your message (Bye to exit)\n");
		  gets(msg);
                  sendconn = sendto(listenfd, msg, sizeof(msg), 0, (struct sockaddr*)&clientstruct, client_len);
                  if (sendconn < 0)
                  {
                        printf("\n[-] SERVER ERROR: Send failed.\n");
                        close(listenfd);
                        exit(1);
                  }
                  else
                        printf("\n[+] SERVER SUCCESS: Send.\n");
            }
      }
      close(listenfd);
      return 0;
}
