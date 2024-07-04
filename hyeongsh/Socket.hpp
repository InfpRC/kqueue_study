
#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <iostream>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 100

class Socket {
	protected:
		int sock;
		struct sockaddr_in address;
		socklen_t address_size;
		char send_buf[BUFFER_SIZE];
		char recv_buf[BUFFER_SIZE];

	public:
		Socket();
		virtual ~Socket();
		
		int sendSocket();
		int recvSocket();

		int getSock() const;
};


#endif
