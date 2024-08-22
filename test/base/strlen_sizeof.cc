#include <iostream>
#include <cstring>

void func(char arr[]) {
        std::cout << "sizeof: " << sizeof(arr) << std::endl;
    std::cout << "strlen: " << std::strlen(arr) << std::endl;
}

template<typename T, size_t N>
void func1(const T (&arr)[N]) {
    std::cout << "sizeof: " << sizeof(arr) << ", N: " << N << std::endl;
    std::cout << "strlen: " << std::strlen(arr) << std::endl;
}

int main() {
    char arr[] = "hello";
    // std::cout << "sizeof: " << sizeof(arr) << std::endl;
    // std::cout << "strlen: " << std::strlen(arr) << std::endl;
    // func(arr);
    func1(arr);
    return 0;
}