#include <iostream>

template<typename T>
class SharedPtr {
    T* ptr_;
    std::size_t count_;
    SharedPtr(T* ptr = nullptr) {
        if (ptr != nullptr) {
            count_ = new int(1);
        } else {
            count_ = new int(0);
        }
    }

    SharedPtr(const SharedPtr& oth) {
        if (this->ptr_ != oth.ptr_) {
            this->ptr_= oth.ptr_;
            this->count_++;
        }
    }

    SharedPtr& operator=(const SharedPtr& oth) {
        if (this->ptr_!= nullptr) {
            if (this->count_ != 0) {
                this->count_--;
            }
            if (this->count_ == 0) {
                delete this->ptr_;
                delete this->count_;
            }

            this->ptr_ = oth.ptr_;
            this->count_ = oth.count_;
            this->count++;
        }
    }

    T* operator->() {
        assert(this->ptr_);
        return this->ptr_;
    }

    T& operator*() {
        assert(this->ptr_);
        return *(this->ptr_);
    }

    ~SharedPtr() {
        if (this->ptr_!= nullptr) {
            if (this->count_ != 0) {
                this->count_--;
                if (this->count_ == 0) {
                    delete this->ptr_;
                    delete this->count_;
                } 
            }
            if (this->count_ == 0) {
                delete this->ptr_;
                delete this->count_;
            }
        }
    }
};

int main() {
    return 0;
}