
#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <iostream>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>

class Socket {
	protected:
		int sock;
		struct sockaddr_in address;
		socklen_t address_size;

	public:
		Socket();
		virtual ~Socket();
		
		int sendSocket();
		int recvSocket();

		int getSock() const;
};


#endif
