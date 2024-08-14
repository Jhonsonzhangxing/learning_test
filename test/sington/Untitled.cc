#include <iostream>
#include <atomic>
#include <mutex>

template<typename T>
class singleton {
    singleton() = default;
    singleton(const T& other) = delete;
    T& operator=(const T& other) = delete;
public:
    T* getInstance() {
        static T* instance = nullptr;
        if (instance == nullptr) {
            static std::once_flag flag;
            std::call_once(flag, []() {
                instance = new (noexcept) T();
            });
        }
        return instance;
    }
};




int mian() {

    return 0;
}