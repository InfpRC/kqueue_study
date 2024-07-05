
#include "Kqueue.hpp"

Kqueue::Kqueue() {
	kq = kqueue();
	if (kq == -1) {
		throw std::runtime_error("kqueue() error");
	}
	timeout.tv_sec = TIME;
	timeout.tv_nsec = 0;
}

Kqueue::~Kqueue() { }

void Kqueue::updateEvent(Socket &sock, int flag) {
	EV_SET(&change, sock.getSock(), EVFILT_READ, flag|EV_ENABLE, 0, 0, NULL);
	if (kevent(kq, &change, 1, NULL, 0, NULL) == -1) {
		throw std::runtime_error("kevent() error");
	}
}

int Kqueue::checkEvent() {
	return kevent(kq, NULL, 0, events, MAX_CLIENTS, &timeout);
}

struct kevent Kqueue::getEvent(int i) {
	return events[i];
}