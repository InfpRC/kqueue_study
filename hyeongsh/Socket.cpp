
#include "Socket.hpp"

Socket::Socket() { }

Socket::~Socket() {
	close(sock);
}

int Socket::sendSocket() {
	return recv(sock, recv_buf, sizeof(recv_buf), 0);
}

int Socket::recvSocket() {
	return send(sock, send_buf, sizeof(send_buf), 0);
}

int Socket::getSock() const {
	return sock;
}