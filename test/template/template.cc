#include<iostream>
#include <type_traits>
#include <concepts>
using namespace std;
// #define H93 0

enum class H93 {
};
enum class H94 {
};

// typedef int H93;
// typedef int H94;
template<typename T>
struct has_big_size {
  static const bool value = false;   //你不是大车
};

template<>
struct has_big_size<H93> {
    static const bool value = true;
};

template<>
struct has_big_size<H94> {
    static const bool value = true;
};

template<typename T, typename std::enable_if_t<has_big_size<T>::value, bool> = true>
void BigCar() {
    std::cout << "test..."<< std::endl;
}
  // uint32_t GetPreviousIdx(uint32_t idx) {
  //     for (size_t i = 1; i < 10; ++i) {
  //       std::cout << "idx: " << idx << std::endl;
  //       uint32_t idx = (i <= idx) ? idx - i : idx;

  //     }
  //   return idx;
  // }
int main() {
    // BigCar<H93>();
    // BigCar<H94>();
    // std::cout << GetPreviousIdx(5) << std::endl;
    return 0;
}


