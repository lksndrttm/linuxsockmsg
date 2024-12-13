#include "logger.h"
#include <fstream>

namespace server
{

Logger::Logger(const std::string& path_to_log) : path_to_log_(path_to_log)
{
}

void Logger::log(const std::string & log_msg)
{
    std::lock_guard lg(cout_mutex_);
    std::fstream fs(path_to_log_, std::ios::out | std::ios::app);
    fs << log_msg << "\n";
}


}
