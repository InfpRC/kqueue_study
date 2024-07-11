
#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>

#include <sys/socket.h>
#include <unistd.h>

#define BUFFER_SIZE 100
#define END 0
#define CONTINUE 1

class Client {
	private:
		int fd;
		std::string recv_buffer;
		std::string send_buffer;
 
	public:
		Client(int _fd);
		~Client();

		int recvSocket();
		int sendSocket();

		void echoService();

		int getFd() const;
		std::string getRecvBuf() const;
		std::string getSendBuf() const;
		void setRecvBuf(std::string message);
		void setSendBuf(std::string message);
		void clearRecvBuf();
		void clearSendBuf();
};

#endif