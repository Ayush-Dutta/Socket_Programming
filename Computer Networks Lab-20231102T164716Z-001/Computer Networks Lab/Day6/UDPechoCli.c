#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct sockaddr_in servstruct, clientstruct;
int listenfd_cli, recvconn, sendconn, serv_len;
unsigned int port = 6667;
char ip[] = "127.0.0.1";
char buffs[128] = "Hello, Server!", buffe[128];

int main()
{
      listenfd_cli = socket(AF_INET, SOCK_DGRAM, 0);
      if (listenfd_cli < 0)
      {
            printf("\n[-] CLIENT ERROR: Socket Creation failed.\n");
            exit(1);
      }
      else
            printf("\n[+] CLIENT SUCCESS: Socket Created.\n");
      servstruct.sin_family = AF_INET;
      servstruct.sin_port = htons(port);
      inet_aton(ip, (&servstruct.sin_addr));
      sendconn = sendto(listenfd_cli, buffs, sizeof(buffs), 0, (struct sockaddr*)&servstruct, sizeof(servstruct));
      if (sendconn < 0)
      {
             printf("\n[-] CLIENT ERROR: Send failed.\n");
             close(listenfd_cli);
             exit(1);
      }
      else
      {
            printf("\n[+] CLIENT SUCCESS: Send.\n");
            recvconn = recvfrom(listenfd_cli, buffe, sizeof(buffe), 0, (struct sockaddr*)&servstruct, &serv_len);
            if (recvconn < 0)
            {
                  printf("\n[-] CLIENT ERROR: Receive failed.\n");
                  close(listenfd_cli);
                  exit(1);
            }
            else
            {
                  printf("\n[+] CLIENT SUCCESS: Receive.\n");
                  printf("\nEchoed Back: %s\n",buffe);
            }
      }
      close(listenfd_cli);
      return 0;
}
