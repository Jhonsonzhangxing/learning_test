#include <iostream>
#include <queue>
#include <mutex>
#include <atomic>
#include <ctime>
#include <chrono>

class service {
    std::queue<std::time_t> q;
    std::mutex mtx_;
    std::atomic<std::queue<std::time_t>> q_;
public:
    void request() {
        std::lock_guard<std::mutex> lck(mtx_);
        std::time_t t = std::time(nullptr);
        q.emplace(t);
        if (t - q.front() > 5) {
            q.pop();
        }

        
    }

    int query() {
        std::lock_guard<std::mutex> lck(mtx_);
        
        return q.size();
    }
};

int main() {

    return 0;
}