#include <iostream>
#include <memory>
#include <mutex>
template<typename T>
class Single {
public:
    Single() = default;
    Single(const T& oth) = delete;
    T& operator=(const T& oth) = delete;
    static T* GetInstance() {
        static T* instance = nullptr;
        if (instance == nullptr) {
            static std::once_flag flag;
            std::call_once(flag,[](){
                instance = new(std::nothrow) T();
                });
        }
        return instance;
    }
};

int main() {
    Single<int> tmp;

    return 0;
}