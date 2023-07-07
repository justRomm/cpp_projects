#ifndef SOCKGUARD_HPP
#define SOCKGUARD_HPP

#include <unistd.h> 
#include <sys/socket.h>

class SocketGuard
{
public:
    explicit SocketGuard(int* _sock)
        : sock(_sock)
    {}

    virtual ~SocketGuard() {
        if(*sock != -1)
            close(*sock);
    }

    SocketGuard(const SocketGuard&) = delete;
    SocketGuard& operator=(const SocketGuard&) = delete;
private:
    int* sock;
};

#endif // SOCKGUARD_HPP