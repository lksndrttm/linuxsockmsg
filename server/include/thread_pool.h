#pragma once

#include <functional>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <queue>
#include <vector>

namespace server {

class ThreadPool
{
  public:
    explicit ThreadPool(int thread_count);
    ~ThreadPool();

    void enqueue(std::move_only_function<void()>&& task);

  private:
    std::queue<std::move_only_function<void()>> task_q_;
    std::vector<std::jthread> w_threads_;
    bool stoped_ = false;
    
    std::condition_variable cv_;
    std::mutex queue_mutex_;

};

}
