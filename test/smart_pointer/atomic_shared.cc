#include <iostream>
#include <atomic>
#include <memory>
#include <mutex>

template <typename T>
class shared_ptr {
	//T* ptr_;
  //size_t* count_;
  std::atomic<T> ptr_;
  std::atomic<size_t> count_
//   std::mutex mtx_;
public:
  shared_ptr(T* ptr) {
    ptr_.store(ptr);
  	if (ptr == nullptr) {
    	//count_ = new int(0);
      count_.store(new int(0));
    } else {
    	//count_ = new int(new int(1));
       count_.store(new int(1));
    }
  }
  
  shared_ptr(const T& oth) {
  	//ptr_ = oth.ptr_;
    //count_ = oth.count_;
    //++(count_);
    ptr_.store(oth.ptr_);
    count_.store(oth.count_);
    count_.fetch_add(1);
    ///////////
    {
      std::unique_lock<std::mutex> lck(mtx_);
    	++(*count_);
    }
    
  }
  
  T& operator=(const T& oth) {
  	if (this != &oth) {
    	ptr_.store(oth.ptr_);
    	count_.store(oth.count_);
      ++(count_);
    }
    return *this;
  }
  
  ~shared_ptr() {
  	if (ptr_.get() != nullptr) {
      {
        std::unique_lock<std::mutex> lck(mtx_);
        if (--*count_ == 0) {
          delete ptr_;
        }
      }
    }
  }
  
  T* operator->() {
  	return this;
  }
  
  T& operator*() {
  	return *this;
  }
  
  size_t use_count() {
  	return count_;
  }
  
  
};