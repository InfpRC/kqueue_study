
#ifndef K_QUEUE_HPP
#define K_QUEUE_HPP

#include <iostream>

#include <sys/event.h>
#include <sys/time.h>

#include "Socket.hpp"

#define MAX_CLIENTS 1024
#define TIME 5

class Kqueue {
	private:
		int kq;
		struct kevent change;
		struct kevent events[MAX_CLIENTS];
		struct timespec timeout;
	
	public:
		Kqueue();
		~Kqueue();
		void updateEvent(int sockfd, int flag);
		int checkEvent();
		struct kevent getEvent(int i);
};

#endif
