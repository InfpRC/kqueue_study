
#ifndef SERVER_HPP
#define SERVER_HPP

#include <map>

#include "Socket.hpp"
#include "Client.hpp"
#include "Kqueue.hpp"
#include "Channel.hpp"

class Server {
	private:
		Socket serv;
		Kqueue kq;
		Channel channel;

		void echoService(Client &clnt);

	public:
		Server(std::string _port);
		~Server();
		void run();
};

#endif
