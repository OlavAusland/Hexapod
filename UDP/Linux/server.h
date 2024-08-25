#include <netinet/in.h>
#include <arpa/inet.h>

namespace UDP
{
    class Server
    {
    private:
        int recv_len{0};

        int sockfd;
        uint16_t port;
        char buffer[512];
        struct sockaddr_in server, client;
    public:
        Server(uint16_t port);
    };
}
