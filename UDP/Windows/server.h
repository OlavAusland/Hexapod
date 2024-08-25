#include <cstdint>
#include <string.h>
#include <winsock2.h>

namespace UDP
{
    class Server
    {
    private:
        struct sockaddr_in server, other;
        
        int slen{sizeof(sockaddr_in)};
        int recv_len{0};
        char buffer[1024];
        
        SOCKET sock;
        uint16_t port;
        WSADATA wsa;
    public:
        Server(uint16_t port);
    };
}
