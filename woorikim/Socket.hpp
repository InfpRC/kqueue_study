// Socket.hpp
#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <cerrno>
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>

class Socket
{
protected:
  int sockfd;

public:
  Socket(int domain, int type, int protocol);
  virtual ~Socket();

  int getFd() const;
  void setNonBlocking();
  void setReuseAddr(bool flag);
  void bind(const struct sockaddr *addr, socklen_t addrlen);
  void listen(int backlog);
  int accept(struct sockaddr *addr, socklen_t *addrlen);
  void send(int client_sock, const char *buffer, size_t length);
  ssize_t recv(int client_sock, char *buffer, size_t length);
};

#endif
