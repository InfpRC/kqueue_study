
#ifndef CLNT_SOCK_HPP
#define CLNT_SOCK_HPP

#include "Socket.hpp"
#include "ServSock.hpp"

class ClntSock : public Socket {
	public:
		ClntSock(ServSock server);
		~ClntSock();
};

#endif