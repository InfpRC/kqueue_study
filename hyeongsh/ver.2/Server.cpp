
#include "Server.hpp"

Server::Server(std::string port, int listen_number) : serv(port, listen_number) {
	kq.updateEvent(serv, EV_ADD);
}

Server::~Server() {}

void Server::run() {
	while (1) {
		int event_num = kq.checkEvent();
		if (event_num == -1) {
			throw std::runtime_error("checkEvent() error");
		}
		for (int i = 0; i < event_num; i++) {
			struct kevent event = kq.getEvent(i);
			if (event.flags & EV_ERROR) {
				throw std::runtime_error("EV_ERROR");
			}
			if (static_cast<int>(event.ident) == serv.getSock()) {
				Socket new_clnt = serv.socketAccept();
				std::cout << new_clnt.getSock() << std::endl;
				clnt.insert(std::make_pair(new_clnt.getSock(), new_clnt));
				kq.updateEvent(new_clnt, EV_ADD);
				std::cout << "connected client: " << new_clnt.getSock() << std::endl;
			} else if (event.filter == EVFILT_READ) {
				Socket event_clnt = clnt.find(static_cast<int>(event.ident))->second;
				event_clnt.recvSocket();
				if (event_clnt.getReadSize() <= 0) {
					std::cout << "closed client: " << event_clnt.getSock() << std::endl;
					kq.updateEvent(event_clnt, EV_DELETE);
					clnt.erase(event_clnt.getSock());
					close(event_clnt.getSock());
				} else {
					echoService(event_clnt);
				}
			}
		}
	}
	close(serv.getSock());
}

void Server::echoService(Socket sock) {
	sock.sendSocket(sock.getBuf());
	memset(sock.getBuf(), 0, BUFFER_SIZE);
}
