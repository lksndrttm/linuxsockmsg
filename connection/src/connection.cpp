#include "connection.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstddef>
#include <unistd.h>
#include "exceptions.h"


namespace conn 
{

std::unique_ptr<Connection> Connection::connect(int port)
{
    struct sockaddr_in addr;

    int sock = socket(AF_INET, SOCK_STREAM, 0);

    if(sock < 0) {
        throw SocketCreationError();
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    if(::connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        throw ConnectionError();
    }

    return std::unique_ptr<Connection>(new Connection(sock));
}


Connection::Connection(int sd) : socket_(sd), closed_(false)
{}

Connection::~Connection()
{
    if(!closed_) {
        ::close(socket_);
    }
}


Connection::Connection(Connection&& other)
{
    socket_ = other.socket_;
    other.closed_ = true;
}

Connection& Connection::operator=(Connection&& other)
{
    if(this != &other) {
        socket_ = other.socket_;
        other.closed_ = true;
    }
    return *this;
}

void Connection::send(const std::string& msg)
{
    if(closed_) {
        throw UsingClosedConnection(); 
    }
    
    std::int32_t msg_size = msg.size();
    send(reinterpret_cast<const std::byte*>(&msg_size), sizeof(msg_size));
    send(reinterpret_cast<const std::byte*>(msg.data()), msg.size());
}


void Connection::send(const std::byte* buf, int len)
{
    if(closed_) {
        throw UsingClosedConnection();
    }

    int total = 0;
    int n;

    while(total < len) {
        n = ::send(socket_, reinterpret_cast<const char*>(buf)+total, len-total, 0);
        
        if(n == -1) {
            break;
        }

        total += n;
    }

    if(n == -1) {
        throw SendError();
    }

}


std::string Connection::receive()
{
    size_t msg_size = *reinterpret_cast<std::int32_t*>(receive(sizeof(std::int32_t)).data());
    std::string msg{reinterpret_cast<char*>(receive(msg_size).data()), msg_size};
    return msg;
}




std::vector<std::byte> Connection::receive(int len)
{
    if(closed_) {
        throw std::runtime_error("Cant receive from closed connection.");
    }

    int total = 0;
    int n;
    const int BUF_SIZE = 1024;
    std::byte buf[BUF_SIZE];
    int msg_size = std::min(BUF_SIZE, len);

    std::vector<std::byte> received;
    received.reserve(len);


    while(total < len) {
        n = ::recv(socket_, reinterpret_cast<char*>(buf), msg_size, 0);
        if(n == 0) {
            throw ReceiveError(); 
        }

        total += n;
        auto beg = std::begin(buf);
        received.insert(received.end(), beg, beg + n);
    }
 
    return received;
}



}
