#pragma once
#include <string>
#include <vector>
#include <cstddef>
#include <memory>
#include "exceptions.h"

namespace conn 
{

class Connection
{
  public:
    void send(const std::string& msg);
    std::string receive();
    
    ~Connection();

    Connection(Connection&& other);
    Connection& operator=(Connection&& other);

    Connection(const Connection&) = delete;
    Connection& operator=(const Connection&) = delete;

    static std::unique_ptr<Connection> connect(int port);

  private:
    explicit Connection(int sd);
    
    std::vector<std::byte> receive(int len);
    void send(const std::byte* buf, int len);
    
    int socket_;
    bool closed_;

    friend class ConnectionManager; 
};

}
