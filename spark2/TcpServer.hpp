#ifndef TcpServer_H
#define TcpServer_H

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <vector>
#include <algorithm>

#define BUFFER_SIZE 100
#define MAX_CLIENTS 1024

class TcpServer {
public:
    TcpServer(int port);
    ~TcpServer();
    void run();

private:
    int serv_sock;
    int kq;
    struct sockaddr_in serv_adr;
    std::vector<int> client_sockets;

    void initServer(int port);
    void setNonBlocking(int sock);
    void handleNewConnection();
    void handleClientData(int sockfd);
    void registerEvent(int sock, int filter, int flags);
    void unregisterEvent(int sock);
};

#endif
