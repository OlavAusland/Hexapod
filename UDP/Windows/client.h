#include <string>
#include <winsock2.h>

namespace UDP
{
    class Client 
    {
    private:
        WSADATA wsa;

        SOCKET sock;
        uint16_t port;
        std::string ip;
        struct sockaddr_in server;
    public:
        Client(std::string ip, uint16_t port);
        
        bool ResizeBuffer(unsigned int size);
    };
}
