// EventManager.cpp
#include "EventManager.hpp"

EventManager::EventManager()
{
  kqueue_fd = kqueue();
  if (kqueue_fd == -1)
  {
    perror("kqueue");
    exit(1);
  }
}

EventManager::~EventManager()
{
  close(kqueue_fd);
}

void EventManager::registerEvent(int fd, int filter, int flags, int fflags, intptr_t data, void *udata)
{
  struct kevent change;
  EV_SET(&change, fd, filter, flags, fflags, data, udata);
  if (kevent(kqueue_fd, &change, 1, nullptr, 0, nullptr) == -1)
  {
    perror("kevent");
    exit(1);
  }
}

int EventManager::waitForEvents(struct kevent *events, int max_events, struct timespec *timeout)
{
  return kevent(kqueue_fd, nullptr, 0, events, max_events, timeout);
}
