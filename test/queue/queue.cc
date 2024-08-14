#include <iostream>
#include <vector>
#include <mutex>


template <typename T>
class queue {
private:
    T* data_;
    size_t size_;
    size_t capacity_;
    std::unique_lock<std::mutex> lock_;
    bool is_exit_flag;
public:
    queue() : data_(nullptr),size_(0),capacity_(0),is_exit_flag(false) {

    }

    ~queue() {
        is_exit_flag = true;
        cv.notify_all();
        delete[] data_;
    }

    void resize() {
        if (capacity_ == size_) {
            if (capacity_ == 0) {capacity_ = 1}

            T* tem_data = new T[2*capacity_];
            for (size_t i = 0; i < size_; i++) {
                tem_data[i] = data_[i];
            }
            delete[] data_;
            data_ = tem_data;
        }
    }

    void push(const T& other) {
        //lock 
        lock_.lock();
        if (capacity_ == 0 || size_ == capacity_) {
            resize();
        }
        data_[size_++] = other;
        cv.notify_all();
    }

    T& pop () {
        //lock
        lock_.lock();
        if (size == 0 && cv.wait()) {
            assert();
        }
        if (is_exit_flag) {
            
            return T();
        }
        

        T& ret = data_[0];
        size_--;
        T* tem_data = new T[capacity_];
        for (size_t i= 0 ; i < capacity_; ++i) {
            tem_data[i] = data_[i+1];
        }
        delete[] data_;
        data_ = tem_data;
        return ret;
    }

    size_t size() {
        return size_;
    }




};


int main() {
    return 0;
}