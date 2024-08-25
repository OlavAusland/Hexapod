#include "client.h"

using namespace UDP;

Client::Client(std::string ip, uint16_t port)
{
    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        exit(EXIT_FAILURE);
    }

    server.sin_family = AF_INET;
    server.sin_port = port;
    server.sin_addr.s_addr = INADDR_ANY;
    
    int n;
    socklen_t len;

    sendto(sockfd, "Test", 5, MSG_CONFIRM, (const struct sockaddr*)&server, sizeof(server));
}
