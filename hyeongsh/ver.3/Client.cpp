
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

int Client::getFd() const {
	return fd;
}

std::string Client::getRecvBuf() const {
	return recv_buffer;
}

std::string Client::getSendBuf() const {
	return send_buffer;
}

void Client::setRecvBuf(std::string message) {
	recv_buffer = message;
}

void Client::setSendBuf(std::string message) {
	send_buffer = message;
}

void Client::clearRecvBuf() {
	recv_buffer.clear();
}

void Client::clearSendBuf() {
	send_buffer.clear();
}