
#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <iostream>

#include <arpa/inet.h>
#include <fcntl.h>

class Socket {
	private:
		int port;
		int fd;
		struct sockaddr_in address;
		socklen_t address_size;

		void reusePort(int fd);
		void bindSock(int fd);
		void listenSock(int fd, int listen_size);
		void setNonBlock(int fd);

	public:
		Socket(std::string &_port);
		~Socket();

		int acceptSock();

		int getFd();
};


#endif
