#include "server.h"
#include <iostream>
#include <winsock2.h>

#pragma comment(lib,"ws2_32.lib")


UDP::Server::Server(uint16_t port)
    : port(port)
{
    if(WSAStartup(MAKEWORD(2,2), &wsa) != 0)
    {
        std::cout << "Failed: " << WSAGetLastError() << '\n';
        exit(EXIT_FAILURE);
    }

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    if(sock == INVALID_SOCKET)
    {
        std::cout << "Failed: Could not create socket: " << WSAGetLastError() << '\n';
        exit(EXIT_FAILURE);
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);

    if(bind(sock, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
    {
        std::cout << "Failed: Could not bind socket: " << WSAGetLastError() << '\n';
        exit(EXIT_FAILURE);
    }

    while(true)
    {
        std::cout << "Waiting for data...\n";
        fflush(stdout);

        memset(buffer, '\0', 1024);
        if((recv_len = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr*)&other, &slen)) == SOCKET_ERROR)
        {
            std::cout << "recvfrom() failed with error code: " << WSAGetLastError() << '\n';
            exit(EXIT_FAILURE);
        }

        std::cout << buffer << '\n';
    }

    closesocket(sock);
    WSACleanup();
}
