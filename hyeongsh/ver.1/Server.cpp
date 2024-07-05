
#include "Server.hpp"

Server::Server(std::string port, int listen_number) : serv(port, listen_number) { }

Server::~Server() { }

void Server::run() {
	kq.updateEvent(serv.getSock(), EV_ADD);
	while (1) {
		int nev = kq.checkEvent();
		if (nev == -1) {
			throw std::runtime_error("checkEvent() error");
		}
		for (int i = 0; i < nev; i++) {
			struct kevent event = kq.getEvent(i);
			if (event.flags & EV_ERROR) {
				throw std::runtime_error("EV_ERROR");
			}
			if (static_cast<int>(event.ident) == serv.getSock()) {
				ClntSock clnt(serv);
				kq.updateEvent(clnt.getSock(), EV_ADD);
				std::cout << "connected client: " << clnt.getSock() << std::endl;
			} else if (event.filter == EVFILT_READ) {
				int sockfd = event.ident;
				int str_len = recvSocket(sockfd);
				if (str_len <= 0) {
					std::cout << "closed client: " << sockfd << std::endl;
					kq.updateEvent(sockfd, EV_DELETE);
					close(sockfd);
					std::cout << "here!\n";
				} else {
					strcpy(send_buf, recv_buf);
					sendSocket(sockfd);
				}
			}
		}
	}
	close(serv.getSock());
}

int Server::sendSocket(int sock) {
	return recv(sock, recv_buf, sizeof(recv_buf), 0);
}

int Server::recvSocket(int sock) {
	return send(sock, send_buf, sizeof(send_buf), 0);
}