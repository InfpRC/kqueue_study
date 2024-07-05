
#ifndef SERVER_HPP
#define SERVER_HPP

#include <map>

#include "Socket.hpp"
#include "Kqueue.hpp"

class Server {
	private:
		Kqueue kq;
		Socket serv;
		std::map< int, Socket > clnt;

		void echoService(Socket sock);

	public:
		Server(std::string port, int listen_number);
		~Server();
		void run();
};

#endif
