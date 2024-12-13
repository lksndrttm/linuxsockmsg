#pragma once
#include <memory>
#include "connection.h"

namespace conn 
{

class ConnectionManager
{
  public:
    ConnectionManager(int port, int max_pending = 100);
    ~ConnectionManager();

    ConnectionManager(const ConnectionManager&) = delete;
    ConnectionManager& operator=(const ConnectionManager&) = delete;

    ConnectionManager(ConnectionManager&&);
    ConnectionManager& operator=(ConnectionManager&&);

    std::unique_ptr<Connection> accept();

  private:
    int listener_;
    bool closed_;
};

}
