#include <iostream>
#include <mutex>
#include <deque>
#include <condition_variable>

template <typename T>
class Queue {
    std::deque<T> queue_;
    std::mutex mutex_;
    std::condition_variable cond_;
public:
    Queue() = default;

    void push(const T& value) {
        // std::lock_guard<std::mutex> lock(mutex_);
        std::unique_lock<std::mutex> lock(mutex_);
        queue_.push_back(value);
        cond_.notify_one();
    }

    bool pop(T& value) {
        std::unique_lock<std::mutex> lock(mutex_);
        if (queue_.empty()) {
            cond_.wait(lock);
        }
    }

};