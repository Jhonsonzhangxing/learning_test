#include <iostream>
#include <atomic>
#include <memory>

template<typename T>
class Singlton {
    Singlton() = default;
    Singlton(const T& oth) = delete;
    T operator=(const T& oth) = delete;
public:
    static T* getInstance() {
        static T* sington = nullptr;
        if (sington == nullptr) {
            static std::once_flag flag;
            std::call_once(flag,[](){sington = new(noexcept) T()})
        }
    }
};