
#ifndef SERV_SOCK_HPP
#define SERV_SOCK_HPP

#include "Socket.hpp"

class ServSock : public Socket {
	public:
		ServSock(std::string port, int listen_number);
		~ServSock();
};

#endif