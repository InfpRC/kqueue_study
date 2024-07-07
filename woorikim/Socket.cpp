#include "Socket.hpp"

Socket::Socket(int domain, int type, int protocol)
{
  sockfd = socket(domain, type, protocol);
  if (sockfd == -1)
  {
    perror("socket");
    exit(1);
  }
}

Socket::~Socket()
{
  close(sockfd);
}

int Socket::getFd() const
{
  return sockfd;
}

void Socket::setNonBlocking()
{
  fcntl(sockfd, F_SETFL, O_NONBLOCK);
}

void Socket::setReuseAddr(bool flag)
{
  int option = flag ? 1 : 0;
  setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
}

void Socket::bind(const struct sockaddr *addr, socklen_t addrlen)
{
  if (::bind(sockfd, addr, addrlen) == -1)
  {
    perror("bind");
    exit(1);
  }
}

void Socket::listen(int backlog)
{
  if (::listen(sockfd, backlog) == -1)
  {
    perror("listen");
    exit(1);
  }
}

int Socket::accept(struct sockaddr *addr, socklen_t *addrlen)
{
  return ::accept(sockfd, addr, addrlen);
}

void Socket::send(int client_sock, const char *buffer, size_t length)
{
  ::send(client_sock, buffer, length, 0);
}

ssize_t Socket::recv(int client_sock, char *buffer, size_t length)
{
  return ::recv(client_sock, buffer, length, 0);
}
