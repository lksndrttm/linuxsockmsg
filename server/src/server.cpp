#include "server.h"
#include <functional>
#include <string>
#include <syncstream>
#include <iostream>

namespace server
{

Server::Server(int port, int max_pending, int thread_count) : connection_manager_(port, max_pending), thread_pool_(thread_count)
{

}


void Server::start()
{
    while(true){
        auto connection = this->connection_manager_.accept();

        std::move_only_function<void()> handle_connection = [this, connection = std::move(connection)] {
            try {
                std::string msg = connection->receive();
                this->logger_.log(msg);
            } catch(const conn::NetworkError& e) {
                std::osyncstream s_cout(std::cout);
                s_cout << e.what() << "\n";
            }
        };

        this->thread_pool_.enqueue(std::move(handle_connection));
    }
}

}
