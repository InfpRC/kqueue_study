#include "TcpServer.hpp"

TcpServer::TcpServer(int port) {
    initServer(port);

    kq = kqueue();
    if (kq == -1) {
        perror("kqueue");
        exit(1);
    }

    registerEvent(serv_sock, EVFILT_READ, EV_ADD | EV_ENABLE);
}

TcpServer::~TcpServer() {
    close(serv_sock);
    for (std::vector<int>::iterator it = client_sockets.begin(); it != client_sockets.end(); ++it) {
        close(*it);
    }
}

void TcpServer::initServer(int port) {
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1) {
        perror("socket");
        exit(1);
    }

    int option = 1;
    setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(port);

    if (bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1) {
        std::cerr << "bind() error" << std::endl;
        exit(1);
    }
    if (listen(serv_sock, 10) == -1) {
        std::cerr << "listen() error" << std::endl;
        exit(1);
    }

    setNonBlocking(serv_sock);
}

void TcpServer::setNonBlocking(int sock) {
    fcntl(sock, F_SETFL, O_NONBLOCK);
}

void TcpServer::registerEvent(int sock, int filter, int flags) {
    struct kevent change;
    EV_SET(&change, sock, filter, flags, 0, 0, NULL);
    if (kevent(kq, &change, 1, NULL, 0, NULL) == -1) {
        perror("kevent");
        exit(1);
    }
}

void TcpServer::unregisterEvent(int sock) {
    struct kevent change;
    EV_SET(&change, sock, EVFILT_READ, EV_DELETE | EV_DISABLE, 0, 0, NULL);
    if (kevent(kq, &change, 1, NULL, 0, NULL) == -1) {
        perror("kevent");
        exit(1);
    }
}

void TcpServer::handleNewConnection() {
    struct sockaddr_in clnt_adr;
    socklen_t adr_sz = sizeof(clnt_adr);
    int clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &adr_sz);
    if (clnt_sock == -1) {
        perror("accept");
        return;
    }

    setNonBlocking(clnt_sock);
    registerEvent(clnt_sock, EVFILT_READ, EV_ADD | EV_ENABLE);
    client_sockets.push_back(clnt_sock);

    std::cout << "connected client: " << clnt_sock << std::endl;
}

void TcpServer::handleClientData(int sockfd) {
    char buf[BUFFER_SIZE];
    int str_len = recv(sockfd, buf, sizeof(buf), 0);
    if (str_len <= 0) {
        std::cout << "closed client: " << sockfd << std::endl;
        unregisterEvent(sockfd);
        close(sockfd);
        client_sockets.erase(std::remove(client_sockets.begin(), client_sockets.end(), sockfd), client_sockets.end());
    } else {
        send(sockfd, buf, str_len, 0);
    }
}

void TcpServer::run() {
    struct timespec timeout;
    timeout.tv_sec = 5;
    timeout.tv_nsec = 0;

    while (1) {
        struct kevent events[MAX_CLIENTS];
        int nev = kevent(kq, NULL, 0, events, MAX_CLIENTS, &timeout);
        if (nev == -1) {
            perror("kevent");
            break;
        }
        for (int i = 0; i < nev; i++) {
            if (events[i].flags & EV_ERROR) {
                std::cerr << "EV_ERROR: " << events[i].data << std::endl;
            }
            if (events[i].ident == (uintptr_t)serv_sock) {
                handleNewConnection();
            } else if (events[i].filter == EVFILT_READ) {
                handleClientData(events[i].ident);
            }
        }
    }
}
