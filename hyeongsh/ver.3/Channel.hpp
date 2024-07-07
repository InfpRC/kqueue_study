
#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <map>

#include "Client.hpp"

class Channel {
	private:
		std::map< int, Client > clnt_map;

	public:
		Channel();
		~Channel();

		void initClient(int fd);
		void delClient(int fd);
		Client &getClient(int fd);
};

#endif
