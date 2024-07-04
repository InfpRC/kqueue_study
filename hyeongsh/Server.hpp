
#ifndef SERVER_HPP
#define SERVER_HPP

#include "ServSock.hpp"
#include "ClntSock.hpp"
#include "Kqueue.hpp"

#define BUFFER_SIZE 100

class Server {
	private:
		ServSock serv;
		Kqueue kq;
		char send_buf[BUFFER_SIZE];
		char recv_buf[BUFFER_SIZE];

		int sendSocket(int sock);
		int recvSocket(int sock);

	public:
		Server(std::string port, int listen_number);
		~Server();
		void run();
};

#endif
