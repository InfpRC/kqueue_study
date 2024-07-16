
#include "Server.hpp"

Server::Server(std::string _port, std::string _password) : serv(_port, _password), kq(), channel() {}

Server::~Server() {}

void Server::run() {
	kq.addEvent(serv.getFd(), EVFILT_READ);
	kq.updateEvent();
	while (1) {
		int size = kq.updateEvent();
		for (int i = 0; i < size; i++) {
			struct kevent event = kq.getEvent(i);
			if (event.flags & EV_ERROR) {
				std::cerr << "EV_ERROR: " << event.data << std::endl;
			}
			if (static_cast<int>(event.ident) == serv.getFd()) {
				int clnt_sock = serv.acceptSock();
				channel.initClient(clnt_sock);
				kq.addEvent(clnt_sock, EVFILT_READ);
				std::cout << "connected client: " << clnt_sock << std::endl;
			} else if (event.filter == EVFILT_READ) {
				Client &clnt = channel.getClient(event.ident);
				int clnt_fd = clnt.getFd();
				int result = clnt.recvSocket();
				if (result == EOF) {
					std::cout << "closed client: " << clnt_fd << std::endl;
					channel.delClient(clnt_fd);
					close(clnt_fd);
				} else if (result == END) {
					//echoService(clnt);
					//channelService(clnt);
					parsing(clnt);
				} else {
					continue ;
				}
			} else if (event.filter == EVFILT_WRITE) {
				Client &clnt = channel.getClient(event.ident);
				if (clnt.sendSocket()) {
					kq.delEvent(clnt.getFd(), EVFILT_WRITE);
				}
			}
		}
	}
	close(serv.getFd());
}

void Server::echoService(Client &clnt) {
	clnt.setSendBuf(clnt.getRecvBuf());
	clnt.clearRecvBuf();
	kq.addEvent(clnt.getFd(), EVFILT_WRITE);
}

void Server::channelService(Client &clnt) {
	std::string message = clnt.getRecvBuf();
	Channel::iterator user = channel.begin();
	while (user != channel.end()) {
		user->second.setSendBuf(clnt.getRecvBuf());
		kq.addEvent(user->first, EVFILT_WRITE);
		user++;
	}
	clnt.clearRecvBuf();
}

void Server::parsing(Client &clnt) {
	while (clnt.getRecvBuf().size()) {
		std::cout << clnt.getRecvBuf() << ":::" << std::endl;
		Message message(&clnt);
		if (message.getCommand() == "NICK") {
			clnt.setNickname(message.getParams(0));
		} else if (message.getCommand() == "USER") {
			clnt.setUsername(message.getParams(0));
			clnt.setRealname(message.getParams(3));
			clnt.setSendBuf(":irc.seoul42.com 001 " + clnt.getNickname() + " :Welcome to the Internet Relay Network randomuser\n");
			clnt.setSendBuf(":irc.seoul42.com 002 " + clnt.getNickname() + " :Your host is irc.seoul42.com\n");
			clnt.setSendBuf(":irc.seoul42.com 003 " + clnt.getNickname() + " :This server was created Mon Jul 9 2024 at 10:00:00 GMT\n");
			clnt.setSendBuf(":irc.seoul42.com 004 " + clnt.getNickname() + " :irc.example.com 1.0 o o\n");
			kq.addEvent(clnt.getFd(), EVFILT_WRITE);
		}
	}
}
