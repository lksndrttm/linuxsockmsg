#pragma once
#include <mutex>
#include <string>

namespace server
{

class Logger
{
  public:
    Logger(const std::string& path_to_log = "log.txt");
    void log(const std::string& log_msg);

  private:
    std::mutex cout_mutex_;
    std::string path_to_log_;
};

}
