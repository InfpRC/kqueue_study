
#include "Channel.hpp"

Channel::Channel() {}

Channel::~Channel() {}

void Channel::initClient(int fd) {
	clnt_map.insert(std::make_pair(fd, Client(fd)));
}

void Channel::delClient(int fd) {
	clnt_map.erase(fd);
}


Client &Channel::getClient(int fd) {
	return clnt_map.find(fd)->second;
}
