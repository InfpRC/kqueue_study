
#ifndef SERVER_HPP
#define SERVER_HPP

#include <map>

#include "Socket.hpp"
#include "Client.hpp"
#include "Kqueue.hpp"
#include "Resource.hpp"

class Server {
	private:
		Socket serv;
		Kqueue kq;
		Resource resource;

	public:
		Server(std::string _port);
		~Server();
		void run();
};

#endif
