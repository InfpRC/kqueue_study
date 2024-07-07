// Client.hpp
#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>

class Client
{
public:
  int sockfd;

  Client(int fd);
  ~Client();

  void setNonBlocking();
  ssize_t receive(char *buf, size_t size);
  void send(const char *buf, size_t size);
  void close();
};

#endif
