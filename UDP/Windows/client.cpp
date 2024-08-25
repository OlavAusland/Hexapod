#include "client.h"
#include <iostream>
#include <winsock2.h>

#pragma comment(lib,"ws2_32.lib")

using namespace UDP;

Client::Client(std::string ip, uint16_t port)
    : ip(ip), port(port)
{
    if(WSAStartup(MAKEWORD(2,2), &wsa) != 0)
    {
        std::cout << "UDP Initialization failed:" << WSAGetLastError() << '\n';
        exit(EXIT_FAILURE);
    }
    
    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if(sock == SOCKET_ERROR)
    {
        std::cout << "socket() failed with error code: " << WSAGetLastError() << '\n';
        exit(EXIT_FAILURE);
    }

    memset((char*)&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.S_un.S_addr = inet_addr(ip.c_str());
        
    sendto(sock, "test", 5, 0, (struct sockaddr*)&server, sizeof(server));
}
