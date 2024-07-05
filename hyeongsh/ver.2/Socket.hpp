
#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <iostream>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 100
#define SERV 1
#define CLNT 2

class Socket {
	private:
		int sock;
		struct sockaddr_in address;
		socklen_t address_size;

		int read_size;
		char buf[BUFFER_SIZE];

	public:
		Socket();
		Socket(std::string &port, int &listen_number);
		~Socket();
		
		void sendSocket(const char *message);
		void recvSocket();
		Socket socketAccept();

		int getSock() const;
		int getReadSize() const;
		char *getBuf();
};


#endif
