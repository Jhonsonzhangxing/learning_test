#include <iostream>
#include <tuple>
#include <string>
#include <sstream>
template <typename... T>
void func(T... args) {
    //....
}

void foo() {
    std::cout << "end" << std::endl;
}

template <typename T, typename... Args>
void foo (T first, Args... args) {
    std::cout << first << " ,size: " << sizeof...(args) << std::endl;
    foo(args...);
}

template <class... Args>
void foo1(Args... args) {
    std::initializer_list<int> a {args...};
    for (auto x : a) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
}

template <size_t k = 0, typename tup>
typename std::enable_if<k == std::tuple_size<tup>::value>::type _foo(const tup& t) {
    std::cout << std::endl;
}

template <size_t k = 0, class tup> 
typename std::enable_if< k<std::tuple_size<tup>::value>::type _foo(const tup& t) { 
    std::cout << std::get<k>(t) << " ";
    _foo<k+1, tup>(t);
}

template <class... Args>
void foo2(Args... args) {
    _foo<0>(std::make_tuple(args...));
}

template <class T>
std::string format(const T& t) {
    std::stringstream ss;
    ss << " " << t << " ";
    // ss  << t;
    return ss.str();
}

template <class... Args>
void foo3(Args... args) {
    // (std::cout << ... << format(args)) << std::endl;
    (std::cout << ... << (std::cout << args, " ")) << std::endl;
}

int main() {
    // foo("good", 2, "110");
    // foo1(1,2,3,4,5);
    // foo2("good", 2, "110");
    foo3("good", 2, "110");
    return 0;
}