// EventManager.hpp
#ifndef EVENTMANAGER_HPP
#define EVENTMANAGER_HPP

#include <sys/event.h>
#include <vector>
#include <cerrno>
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>

#define MAX_CLIENTS 1024

class EventManager
{
private:
  int kqueue_fd;

public:
  EventManager();
  ~EventManager();

  void registerEvent(int fd, int filter, int flags, int fflags, intptr_t data, void *udata);
  int waitForEvents(struct kevent *events, int max_events, struct timespec *timeout);
};

#endif
