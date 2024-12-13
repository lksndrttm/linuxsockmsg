#include "client.h"
#include "connection.h"

#include <chrono>
#include <thread>
#include <iostream>
#include <sstream>
#include <iomanip>

namespace client
{

Client::Client(const std::string& name, int port, int reconnect_period) : reconnect_period_(reconnect_period), port_(port), name_(name)
{ 
}

void Client::start()
{
    try {
        while(true) {
            auto connection{conn::Connection::connect(port_)};

            auto const now = std::chrono::current_zone()->to_local(std::chrono::system_clock::now());
            std::string datetime = std::format("{:%Y-%m-%d %X}", now);
            auto time_since_epoch = std::chrono::system_clock::now().time_since_epoch();
            auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(time_since_epoch).count() % 1000;

            std::stringstream ss;
            ss  << datetime << "." << std::setw (3) << std::setfill('0') << milliseconds;
            std::string message = "[" + ss.str() + "] " + name_; 
            std::cout << message << "\n";

            connection->send(message);

            std::this_thread::sleep_for(std::chrono::seconds(reconnect_period_));
        }
    } catch(const conn::NetworkError& e) {
        std::cout << e.what() << "\n";
    }
}

}
