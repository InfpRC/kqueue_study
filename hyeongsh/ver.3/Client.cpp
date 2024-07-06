
#include "Client.hpp"

Client::Client(int _fd) : fd(_fd) {}

Client::~Client() {}

int Client::recvSocket() {
	char buf[BUFFER_SIZE] = {0};
	if (recv(fd, buf, sizeof(buf), 0) <= 0) {
		return EOF;
	}
	recv_buffer.append(buf);
	if (recv_buffer[recv_buffer.size() - 1] == '\n') {
		return END;
	}
	return CONTINUE;
}

int Client::sendSocket() {
	int size = send(fd, send_buffer.c_str(), send_buffer.size(), 0);
	send_buffer.erase(0, size);
	if (send_buffer.size() == 0)
		return true;
	return false;
}

void Client::echoService() {
	send_buffer = recv_buffer;
	recv_buffer.clear();
}

int Client::getFd() {
	return fd;
}