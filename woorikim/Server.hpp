#ifndef SERVER_HPP
#define SERVER_HPP

#include "Socket.hpp"
#include <cstring>
#include <iostream>

class Server : public Socket
{
public:
  Server(int port);
};

#endif
