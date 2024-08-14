#include <iostream>
#include <mutex>
template <typename T>
class Singleton {
public:
    static T& GetInstance() {
        static T instance;
        return instance;
    }
private:
    Singleton() {}
    ~Singleton() {}
    Singleton (const Singleton&) = delete;
    Singleton (Singleton&&) = delete;

    Singleton& operator=(const Singleton&) = delete;
    Singleton& operator=(Singleton&&) = delete;
};

template <typename TT>
class singleton1 {
public:
    static TT* getinstance() {
        static TT* instance = nullptr;
        if (nullptr == instance) {
            static std::once_flag flag;
            std::call_once(flag,[&](){instance = new(std::nothrow) TT();});
        }
    }
private:
    singleton1(){};
    ~singleton1(){};

    singleton1(const singleton1&) = delete;
    singleton1(const singleton1&&) = delete;

    singleton1& operator=(singleton1&) = delete;
    singleton1& operator=(singleton1&&) = delete;
};

#include <memory>

template <typename T>
class SharedPtr {
private:
    T* _ptr;
    size_t* _count;

public:
    SharedPtr(const T* ptr = nullptr):_ptr(ptr) {
        if (nullptr == ptr) {
            this->_count = new size_t(0);
        } else {
            this->_ptr = ptr;
            this->_count = new size_t(1);
        }
    }

    // 拷贝构造
    SharedPtr(const T& ptr) {
        if (&ptr != this){
            this->_ptr = ptr._ptr;
            this->_count =ptr._ptr;
            ++(*this->_count);
        }
    }
    //重载=
    T& operator=(const T& ptr) {
        if (&ptr != this){
            if (this->_ptr != nulptr){
                if(--(*this->_count) == 0) {
                    delete this->_ptr;
                    delete this->_count;
                }
            }

            this->_ptr = ptr._ptr;
            this->_count = ptr._count;
            ++(*this->_count);
        }
    }
    //重载×
    T& operator*() {
        assert(this->_ptr == nullptr);
        return *(this->_ptr);
    }
    //重载->
    T* operator->() {
        assert(this->_ptr == nullptr);
        return this->_ptr;
    }

    //析构
    ~SharedPtr() {
        if (this->_count == 0 || --(*this->_count) == 0) {
            delete this->_ptr;
            delete this->_count;
        }
    }

    size_t use_count() {
        return *this->_count;
    }
};