#pragma once
#include <string>

namespace client
{

class Client
{
  public:
    Client(const std::string& name, int port, int reconnect_period);
    ~Client() = default;

    Client(const Client&) = delete;
    Client& operator=(const Client&) = delete;
    Client(Client&&) = delete;
    Client& operator=(Client&&) = delete;

    void start();

  private:
    int reconnect_period_;
    int port_;
    std::string name_;
};


}
