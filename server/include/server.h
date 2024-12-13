#pragma once

#include "connection_manager.h"
#include "thread_pool.h"
#include "logger.h"


namespace server
{

class Server
{
  public:
    Server(int port, int max_pending, int thread_count);
    void start();

  private:
    conn::ConnectionManager connection_manager_;
    ThreadPool thread_pool_;
    Logger logger_;

};


}
