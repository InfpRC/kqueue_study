#include "Server.hpp"
#include "Client.hpp"
#include "EventManager.hpp"
#include <iostream>
#include <vector>
#include <cstring>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    std::cerr << "Usage: " << argv[0] << " <port>" << std::endl;
    return 1;
  }

  int port = atoi(argv[1]);
  Server server(port);
  EventManager eventManager;

  eventManager.registerEvent(server.getFd(), EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, nullptr);
  std::cout << "Server listening on port " << port << std::endl;

  struct timespec timeout;
  timeout.tv_sec = 5;
  timeout.tv_nsec = 0;

  while (true)
  {
    struct kevent events[MAX_CLIENTS];
    int nev = eventManager.waitForEvents(events, MAX_CLIENTS, &timeout);

    if (nev == -1)
    {
      perror("kevent");
      break;
    }

    for (int i = 0; i < nev; ++i)
    {
      if (events[i].flags & EV_ERROR)
      {
        std::cerr << "EV_ERROR: " << events[i].data << std::endl;
        continue;
      }

      if (static_cast<int>(events[i].ident) == server.getFd())
      {
        // New client connection
        struct sockaddr_in clnt_adr;
        socklen_t adr_sz = sizeof(clnt_adr);
        int clnt_sock = server.accept((struct sockaddr *)&clnt_adr, &adr_sz);
        if (clnt_sock == -1)
        {
          perror("accept");
          continue;
        }

        Client client(clnt_sock);
        client.setNonBlocking();
        eventManager.registerEvent(client.sockfd, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, nullptr);
        std::cout << "Connected client: " << clnt_sock << std::endl;
      }
      else if (events[i].filter == EVFILT_READ)
      {
        // Existing client sends data
        Client client(events[i].ident);
        char buf[BUFFER_SIZE];
        ssize_t str_len = client.receive(buf, sizeof(buf));

        if (str_len <= 0)
        {
          std::cout << "Closed client: " << events[i].ident << std::endl;
          eventManager.registerEvent(events[i].ident, EVFILT_READ, EV_DELETE, 0, 0, nullptr);
          client.close();
        }
        else
        {
          client.send(buf, str_len);
        }
      }
    }
  }

  return 0;
}
