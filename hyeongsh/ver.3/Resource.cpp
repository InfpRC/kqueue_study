
#include "Resource.hpp"

Resource::Resource() {}

Resource::~Resource() {}

void Resource::initClient(int fd) {
	clnt_map.insert(std::make_pair(fd, Client(fd)));
}

void Resource::delClient(int fd) {
	clnt_map.erase(fd);
}


Client &Resource::getClient(int fd) {
	return clnt_map.find(fd)->second;
}
