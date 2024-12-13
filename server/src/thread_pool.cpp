#include "thread_pool.h"

namespace server
{

ThreadPool::ThreadPool(int thread_count)
{
    w_threads_.reserve(thread_count);

    for(int i = 0; i < thread_count; ++i) {
        w_threads_.emplace_back([this](){
            std::move_only_function<void()> task;
            
            while(true) {
                {
                    std::unique_lock lk(queue_mutex_);
                    this->cv_.wait(lk, [this]{return this->stoped_ || !this->task_q_.empty();});
                    
                    if(this->stoped_ && this->task_q_.empty()) {
                        return;
                    }

                    task = std::move(this->task_q_.front());
                    this->task_q_.pop();
                }
                
                task();
            }

        });
    }
}

void ThreadPool::enqueue(std::move_only_function<void()>&& task)
{
    {
        std::lock_guard lg(queue_mutex_);
        if(stoped_){
            throw std::runtime_error("Cant enqueue in stoped pull.");
        }
        task_q_.push(std::move(task));
    }
    cv_.notify_one();
}

ThreadPool::~ThreadPool()
{
    {
        std::lock_guard lg(queue_mutex_);
        stoped_ = true;
    }

    cv_.notify_all();

}


}
