#ifndef THREADPOOL_H
#define THREADPOOL_H
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <condition_variable>
#include <functional>
#include <stdexcept>
#include <memory>
#include <queue>
#include <future>

class ThreadPool {
public:
    ThreadPool(size_t);
    ~ThreadPool();
    template<class F, class... Args>
    auto enqueue(F&& f, Args&&... args)
        ->std::future<typename std::result_of<F(Args...)>::type>;

private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    std::mutex queue_mutex;
    std::condition_variable condition;
    bool stop;
};

inline ThreadPool::ThreadPool(size_t threads)
        :stop(false){
            for (size_t i = 0; i < threads; ++i)
                workers.emplace_back(
                    [this]{
                        for(;;){
                            std::function<void()> task;
                            {
                                std::unique_ptr<std::mutex> lock(this->queue_mutex);
                                this->condition.wait(lock,[this]{return this->stop || !this->workers.empty()});
                                if ( this->stop && this->workers.empty()){
                                    return;
                                }

                                task = std::move(this->tasks.front());
                                this->tasks.pop();
                            }
                            task();
                        }
                    }
                );
        }

template<class F, class... Args>
auto ThreadPool::enqueue(F&& f, Args&&... args)
        ->std::future<typename std::result_of<F(Args...)>::type>
{
    using return_type = typename std::result_of<F(Args...)>::type;
    auto task = std::make_shared<std::packaged_task<return_type()>>();
    std::future<return_type> res = task->get_future();
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        if(stop){
            throw std::runtime_error("enqueue on stopped ThreadPool");
        }
        tasks.emplace([task](){*task();});
    }
    condition.notify_one();
    return res;
}

inline ThreadPool::ThreadPool()
{
    {
        std::unique_ptr<std::mutex> lock(queue_mutex);
        stop = true;
    }
    condition.notify_all();
    for (std::thread& worker : workers)
        worker.join();
}

#endif