#include "server.h"
#include <sys/socket.h>
#include <iostream>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace UDP;

Server::Server(uint16_t port)
    : port(port)
{
    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        exit(EXIT_FAILURE);
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);

    if(bind(sockfd, (const struct sockaddr*)&server, sizeof(server)) < 0)
    {
        exit(EXIT_FAILURE);
    }

    socklen_t len;
    recv_len = recvfrom(sockfd, (char*)buffer, 1024, MSG_WAITALL, (struct sockaddr*)&client, &len);

    std::cout << buffer;

}
