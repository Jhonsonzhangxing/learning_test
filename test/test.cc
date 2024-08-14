#include <iostream>
#include <memory>

template <typename T>
class SmartPtr {
private:
    T* ptr;
    size_t* ptr_size;
public:
    SmartPtr(T* ptr == nullptr) : ptr_(ptr) {
        if (_ptr) {
            ptr_size = new size_t(1);
        } else {
            ptr_size = new size_t(0);
        }
    };

    SmartPtr(const SmartPtr& other) {
        if (&other != this){
            _ptr = other.ptr;
            _ptr_size = other.ptr_size;
            (*_ptr_size)++;
        }
    }

    SmartPtr& operator=(const SmartPtr& other) {
        if (&other == this){
            return *this;
        } else (&other != this) {
            if (_ptr) {
                if (--(*_ptr_size) == 0) {
                    delete _ptr;
                    delete _ptr_size;
                }
            }
        }
        _ptr = other.ptr;
        _ptr_size = other.ptr_size;
        (*_ptr_size)++;
    }

    SmartPtr operator* () {
        if (_ptr != nullptr) {
            rerurn *_ptr;
        } else {
            return nullptr;//or assert(true)
        }
    }

    SmartPtr operator->() {
        assert(_ptr == nullptr);
        return this->_ptr;
    }

    ~SmartPtr() {
        if (*_ptr_size == 0) {
            delete _ptr;
            delete _ptr_size;
        } else {
            if (--(*ptr_size) == 0) {
                delete _ptr;
                delete _ptr_size;
            } else {
                _ptr = nullptr;
                _ptr_size = nullptr;
            }
        }
    }

    size_t use_count() {
        return * ptr_size;
    }
};

template <typename T> 
class Singleton {
public:
    static T* getInstance() {
        static T* instance = nullptr;
        if (!instance) {
            static std::once_flag flag;
            std::call_one(flag, [&] { instance = new (std::nothrow) T();});
        }
        return instance;
    }
private:
    Singleton();
    ~Singleton();
    Singleton(const T& other) = delete;
    Singleton& operator=(const Singleton& other) noexcept = delete;
};

#include <iostream>
#include <algorithm>
#include <cassert>

template <typename T>
class Vector{
private:
    T* data;
    size_t capacity;
    size_t size;

    void resize(size_t newCapacity) {
        T* newData = new T[newCapacity];
        // T* data = new T[size];
        // std::copy(data,data+size,newDatat)
        std::copy(data,data+size,newData);
        delete[] data;
        data = newData;
    }
public:
    Vector() : data(nullptr),capacity(0),size(0) {}
    ~Vector() {
        delete[] data;
    }
    void push_back(cont T& value) {
        if (size == capacity) {
            resize(capacity == 0 ? 1 : capacity * 2);
        }
        data[size++] = value;
    }

    size_t size() const {
        return size;
    }

    T& operator[](size_t index){
        return data[index];
    }

    const T& operator[] (size_t index)const {
        return data[index];
    }

    void insert(size_t pos, const T& value) {
        assert(pos >= 0)
        assert(pos <= size);
        if (size == capacity) {
            resize(capacity == 0 ? 1 : capacity * 2);
        }
        size_t i = size - 1;
        while (i > pos) {
            data[i] = data[i-1];
            i--;
        }
        data[pos] = value;
        ++size;
    }
};

int fib(int n) {
    if (n <= 1) return n;
    return (fib(n-1) + fib(n-2));
}

#include <map>
#include <array>
#include <set>
#include <vector>

int fib(int n) {
    if (n <= 1) return n;
    std::vector<int> dp(n+1,-1);
    dp[0] =0; dp[1] = 1;
    for (int i = 2; i <= n; ++i) {
        dp[i] = dp[i-1] + dp[i-2];
    }
    return dp[n];
}

int knapsack() {
    std::vector<int> weight = {2,2,6,5,4};
    std::vector<int> value = {6,3,5,4,6};
    int W = 10;
    int n = weight.size();
    std::vector<std::vector<int>> dp(n+1,std::vector<int>(W+1,0));
    for (int i = 1; i < n; ++i) {
        for (int w = 1; w <= W; ++w) {
            if (weight[i-1] <= w) {
                dp[i][w] = std::max(dp[i-1][w], dp[i-1][w - weight[i-1] + value[i-1]]);
            } else {
                dp[i][w] = dp[i-1][w];
            }
        }
    }
}


int main() {
    std::map<char,int> mymap;
    mymap['a'] = 1;
    mymap.emplace('b',2);
    mymap.insert(std::make_pair('c',3));

    for (std::map<char,int>::iterator it = mymap.begin(); it != mymap.end(); ++it) {
        ;
    }

    std::array<int,3> arr = {1,2,3};
    std::set<int> myset = {1,2,3,4};

    //dp
    std::vector<int> dp(5,-1);
    std::map<std::pair<int,int>, int> memo;
    std::vector<std::vector<int>> myvec(5,std::vector<int>(6,-1));
    std::shared_ptr<Singleton<int>> dp_ptr = std::make_shared<Singleton<int>>();
    return 0;
}

template<typename T>
class SharePtr1 {
private:
    size_t* count;
    T* ptr;
public:
    SharePtr1(T* ptr = nullptr): ptr(ptr) {
        if(ptr != nullptr) {
            count = new size_t(1);
        } else {
            count = new size_t(0);
        }
    }
    ~SharePtr() {
        if (ptr != nullptr && --(*count) == 0) {
            delete ptr;
            delete count;
            ptr = nullptr;
            count = nullptr;
        } 

    }

    SharePtr1(const SharePtr1& other) {
        if (this != &other) {
            if (other.ptr != nullptr) {
                ptr = other.ptr;
                count = other.count;
                ++(*count);
            }
        }
        return *this;
    }

    SharePtr1& operator = (const SharePtr1& other) {
        if (other.ptr != this) {
            if (ptr != nullptr && --(*count) == 0) {
                delete ptr;
                delete count;
            } else {
                ptr = other.ptr;
                count = other.count;
            }
        }
        return *this;
    }

    SharePtr1 operator*() {
        if (ptr != nullptr) {
            return *ptr;
        } else {
            return nullptr;
        }
    }

    SharePtr1 operator->() {
        if (ptr != nullptr) {
            return ptr;
        } else {
            assert();
        }
    }
};

template <typename T>
class vector {
private:
    T* data_;
    size_t capacity_;
    size_t size_;
public:
    vector(size_t capacity) : capacity_(capacity) {
        data_ = new T[capacity];
        size_ = 0;
    }

    ~vector() {
        delete[] data_;
    }

    T& operator[] (size_t index) {
        return data_[index];
    }

    void push_back(const T& value) {
        if (size_ == capacity_) {
            resize((capacity_ == 0) ? 1 : capacity_ * 2);
        }
        data_[size_++] = value;
    }

    void resize(size_t size) {
        if (size > size_) {
            T* new_data = new T[size];
            std::copy(data_,data_+size_,new_data);
            delete[] data_;
            data_ = new_data;
        }
    }

    size_t size() const {
        reture size_;
    }
};

template <typename T>
class singleton {
private:
    singleton() = default;
    ~singleton() = default;
    singleton(const T& other) = delete;
    T& operator = (const T& other) = delete;
public:
    static T* getInstance() {
        static T* instance = nullptr;
        if (!instance) {
            static std::once_flag flag;
            std::call_once(flag,[&](){instance = new (noexcept)T();});
        }
        return instance;
    }
};



template <typename T>
class singleton {
    singleton() = default;
    ~singleton() = default;
    singleton(const T& oth) = delete;
    singleton& operator=(const T& oth) = delete;
public:
    static T* getInstance() {
        static T* instance = nullptr;
        if (!instance) {
            std::once_flag flag;
            std::call_once(flag,[&](){instance = new(noexcept) T();})
        }
        return instance;
    }
};

int fib(int n) {
    if (n <= 1) return n;
    return (fib(n-1) + fib(n-2));
}