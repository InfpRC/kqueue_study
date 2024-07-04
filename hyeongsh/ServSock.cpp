
#include "ServSock.hpp"

ServSock::ServSock(std::string &port, int &listen_number) : Socket() {
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

ServSock::~ServSock() { }