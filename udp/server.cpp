#include <iostream>
#include <string>

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main() {
  int sock = socket(AF_INET, SOCK_DGRAM, 0);
  sockaddr_in addr = { 0 };

  if( sock < 0 ) {
    return 1;
  }

  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr("0.0.0.0");
  addr.sin_port = htons(80);

  bind(sock, (sockaddr*)&addr, sizeof(addr));

  char buf[0x1000] { 0 };

  recv(sock, buf, sizeof(buf), 0);

  std::cout << buf << std::endl;

}