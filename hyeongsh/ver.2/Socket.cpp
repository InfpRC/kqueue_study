
#include "Socket.hpp"

Socket::Socket() : address_size(sizeof(address)) { }

Socket::Socket(std::string &port, int &listen_number) {
	sock = socket(PF_INET, SOCK_STREAM, 0);
	if (sock == -1)
		throw std::runtime_error("socket() error");

	int option = true;
	int optlen = sizeof(option);
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (void *)&option, optlen);

	memset(&address, 0, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = htonl(INADDR_ANY);
	address.sin_port = htons(strtod(port.c_str(), 0));

	if (bind(sock, (struct sockaddr *)&address, sizeof(address)) == -1)
		throw std::runtime_error("bind() error");

	if (listen(sock, listen_number) == -1)
		throw std::runtime_error("listen() error");

	fcntl(sock, F_SETFL, O_NONBLOCK);
}

Socket::~Socket() {}

void Socket::sendSocket(const char *message) {
	send(sock, message, read_size, 0);
}

void Socket::recvSocket() {
	read_size = recv(sock, buf, sizeof(buf), 0);
}

Socket Socket::socketAccept() {
	Socket clnt;
	clnt.sock = accept(sock, (struct sockaddr *)&clnt.address, &address_size);
	if (clnt.sock == -1)
		throw std::runtime_error("accept() error");
	fcntl(clnt.sock, F_SETFL, O_NONBLOCK);
	return clnt;
}

int Socket::getSock() const {
	return sock;
}

int Socket::getReadSize() const {
	return read_size;
}

char *Socket::getBuf() {
	return buf;
}
