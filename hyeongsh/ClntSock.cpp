
#include "ClntSock.hpp"

ClntSock::ClntSock() {}

ClntSock::ClntSock(ServSock server) : Socket() {
	sock = accept(server.getSock(), (struct sockaddr *)&address, &address_size);
	fcntl(sock, F_SETFL, O_NONBLOCK);
}

ClntSock::~ClntSock() { }