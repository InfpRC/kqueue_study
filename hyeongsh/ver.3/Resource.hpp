
#ifndef RESOURCE_HPP
#define RESOURCE_HPP

#include <map>

#include "Client.hpp"

class Resource {
	private:
		std::map< int, Client > clnt_map;

	public:
		Resource();
		~Resource();

		void initClient(int fd);
		void delClient(int fd);
		Client &getClient(int fd);
};

#endif
