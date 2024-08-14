#include <iostream>
#include <atomic>
#include <mutex>
template<typename T, size_t Cap>
class queue {
    T* data_[Cap];
    // std::atomic<size_t> head_{0}, tail_{0}, write{0};
    size_t head{0},tail{0},size{0};
    std::mutex mutex_;
public:
    queue() = default;
    queue(const queue& other) = delete;
    queue& operator=(const queue& other) = delete;

    bool push(const T& value) {
        std::unique_lock<std::mutex> lck(mutex_);
        if ((tail + 1) % Cap == head) return false;
        data_[tail++] = value;
        return true;
    }

    bool pop(T& value) {
        std::unique_lock<std::mutex> lck(mutex_);
        if (head == tail) return false;
        value = data_[head++];
        return true;
    }

    size_t size() {
        std::unique_lock<std::mutex> lck(mutex_);
        return tail - head;
    }
};




int main() {

    return 0;
}