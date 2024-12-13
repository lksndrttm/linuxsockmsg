#include "connection_manager.h"
#include "connection.h"
#include "exceptions.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstddef>
#include <unistd.h>

namespace conn
{

ConnectionManager::ConnectionManager(int port, int max_pending) : closed_(false)
{
    struct sockaddr_in addr;

    listener_ = socket(AF_INET, SOCK_STREAM, 0);
    if(listener_ < 0) {
        throw SocketCreationError();
    }
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(listener_, (struct sockaddr*) &addr, sizeof(addr)) < 0) {
        throw SocketBindError();
    }

    listen(listener_, max_pending);
    
}

std::unique_ptr<Connection> ConnectionManager::accept()
{ 
    int sock = ::accept(listener_, NULL, NULL);
    if(sock < 0) {
        throw SocketCreationError();
    }

    return std::unique_ptr<Connection>(new Connection(sock));
}

ConnectionManager::~ConnectionManager()
{
    if(!closed_) {
        close(listener_);
    }
}

ConnectionManager::ConnectionManager(ConnectionManager&& other)
{
    other.closed_ = true;
    listener_ = other.listener_;
}


ConnectionManager& ConnectionManager::operator=(ConnectionManager&& other)
{
    if(this != &other) {
        other.closed_ = true;
        listener_ = other.listener_;
    }
    return *this;
}


}
