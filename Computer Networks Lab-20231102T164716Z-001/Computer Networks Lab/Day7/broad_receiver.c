#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct sockaddr_in sendstruct, receivestruct;
int listenfd_cli, bindconn, recvconn, send_len;
unsigned int port = 6667;
char buff[128];

int main()
{
      listenfd_cli = socket(AF_INET, SOCK_DGRAM, 0);
      if (listenfd_cli < 0)
      {
            printf("\n[-] RECEIVER ERROR: Socket Creation failed.\n");
            exit(1);
      }
      else
            printf("\n[+] RECEIVER SUCCESS: Socket Created.\n");
      sendstruct.sin_family = AF_INET;
      sendstruct.sin_port = htons(port);
      //inet_aton(ip, (&servstruct.sin_addr));
      sendstruct.sin_addr.s_addr = htonl(INADDR_ANY);
      bindconn = bind(listenfd_cli, (struct sockaddr*)&sendstruct, sizeof(sendstruct));
      if (bindconn < 0)
      {
            printf("\n[-] RECEIVER ERROR: Bind failed.\n");
            close(listenfd_cli);
            exit(1);
      }
      else
            printf("\n[+] RECEIVER SUCCESS: Bind.\n");
      send_len = sizeof(sendstruct);
      recvconn = recvfrom(listenfd_cli, buff, sizeof(buff), 0, (struct sockaddr*)&sendstruct, &send_len);
      if (recvconn < 0)
      {
             printf("\n[-] RECEIVER ERROR: Receive failed.\n");
             close(listenfd_cli);
             exit(1);
      }
      else
      {
                  printf("\n[+] RECEIVER SUCCESS: Received.\n");
                  printf("\n%s\n",buff);
      }
      close(listenfd_cli);
      return 0;
}
