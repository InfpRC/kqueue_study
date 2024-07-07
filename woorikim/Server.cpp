// Server.cpp
#include "Server.hpp"

Server::Server(int port) : Socket(PF_INET, SOCK_STREAM, 0)
{
  setReuseAddr(true);
  setNonBlocking();
  struct sockaddr_in serv_adr;
  memset(&serv_adr, 0, sizeof(serv_adr));
  serv_adr.sin_family = AF_INET;
  serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_adr.sin_port = htons(port);
  bind((struct sockaddr *)&serv_adr, sizeof(serv_adr));
  listen(10);
}
