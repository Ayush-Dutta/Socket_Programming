#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct sockaddr_in sendstruct, receivestruct;
int listenfd, opt_val, opt_len, send_len, sendconn;
unsigned int port = 6667;
char ip[] = "192.168.6.255";
char msg[128] = "BROADCAST";

int main()
{
      listenfd = socket(AF_INET, SOCK_DGRAM, 0);
      if (listenfd < 0)
      {
            printf("\n[-] SENDER ERROR: Socket Creation failed.\n");
            exit(1);
      }
      else
            printf("\n[+] SENDER SUCCESS: Socket Created.\n");
      opt_val = 1;
      opt_len = sizeof(opt_val);
      setsockopt(listenfd, SOL_SOCKET, SO_BROADCAST, (void *)&opt_val, opt_len);
      sendstruct.sin_family = AF_INET;
      sendstruct.sin_port = htons(port);
      //inet_aton(ip, (&sendstruct.sin_addr));
      sendstruct.sin_addr.s_addr = inet_addr(ip);
      send_len = sizeof(sendstruct);
      sendconn = sendto(listenfd, msg, sizeof(msg), 0, (struct sockaddr*)&sendstruct, &send_len);
      if (sendconn < 0)
      {
            printf("\n[-] SENDER ERROR: Send failed.\n");
            close(listenfd);
            exit(1);
      }
      printf("\n[+] SENDER SUCCESS: Sent.\n");
      close(listenfd);
      return 0;
}
