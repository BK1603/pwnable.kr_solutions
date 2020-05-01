#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

int main() {
  int sd;
  struct addrinfo hints;
  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  struct addrinfo *servinfo;
  printf("%d\n", getaddrinfo(NULL, "2020", &hints, &servinfo));

  sd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
  printf("%d\n", bind(sd, servinfo->ai_addr, servinfo->ai_addrlen));
  printf("%d\n", connect(sd, servinfo->ai_addr, servinfo->ai_addrlen));

  char buf[5] = "\xde\xad\xbe\xef";
  printf("%ld\n", send(sd, buf, 4, 0));
  close(sd);
  return 0;
}
