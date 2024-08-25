#include <string>
#include <inttypes.h>
#include <netinet/in.h>

namespace UDP
{
    class Client
    {
    private:
        int sockfd;
        char buffer[512];
        struct sockaddr_in server;
    public:
        Client(std::string ip, uint16_t port);
    };
}
