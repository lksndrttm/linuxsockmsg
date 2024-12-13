#pragma once

#include <exception>

namespace conn 
{

class NetworkError : public std::exception
{
  public:
    const char * what() const noexcept override
    {
        return "Network error.";
    }
};

class ConnectionError : public NetworkError
{
  public:
    const char * what() const noexcept override
    {
        return "Connection error.";
    }
};

class SendError : public NetworkError
{
  public:
    const char * what() const noexcept override
    {
        return "Send error.";
    }
};

class ReceiveError : public NetworkError
{
  public:
    const char * what() const noexcept override
    {
        return "Receive error.";
    }
};

class UsingClosedConnection : public NetworkError
{
  public:
    const char * what() const noexcept override
    {
        return "Attempt to use closed connection.";
    }
};

class SocketCreationError : public NetworkError
{
  public:
    const char * what() const noexcept override
    {
        return "Cant create socket.";
    }
};

class SocketBindError : public NetworkError
{
  public:
    const char * what() const noexcept override
    {
        return "Cant bind socket.";
    }
};


}

