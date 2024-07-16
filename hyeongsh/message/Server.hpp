
#ifndef SERVER_HPP
#define SERVER_HPP

#include <map>

#include "Socket.hpp"
#include "Client.hpp"
#include "Kqueue.hpp"
#include "Channel.hpp"
#include "Message.hpp"

class Server {
	private:
		Socket serv;
		Kqueue kq;
		Channel channel;

		void echoService(Client &clnt);
		void channelService(Client &clnt);
		void parsing(Client &clnt);

	public:
		Server(std::string _port, std::string _password);
		~Server();
		void run();
};

#endif
