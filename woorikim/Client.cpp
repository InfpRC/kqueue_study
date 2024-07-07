#include "Client.hpp"

Client::Client(int fd) : sockfd(fd) {}

Client::~Client()
{
}

void Client::setNonBlocking()
{
  fcntl(sockfd, F_SETFL, O_NONBLOCK);
}

ssize_t Client::receive(char *buf, size_t size)
{
  return ::recv(sockfd, buf, size, 0);
}

void Client::send(const char *buf, size_t size)
{
  ::send(sockfd, buf, size, 0);
}

void Client::close()
{
  ::close(sockfd);
}
