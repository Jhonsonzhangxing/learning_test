#include <iostream>
#include <cstring>

void func(char arr[]) {
    std::cout << "sizeof: " << sizeof(arr) << ", strlen: " << std::strlen(arr)<< std::endl;
}

template<typename T, size_t N>
void func1(T (&arr)[N]) {
    std::cout << "sizeof: " << sizeof(arr) << ", N: " << N << std::endl;
    std::cout << "strlen: " << strlen(arr) << ", N: " << N << std::endl;
}


int main() {
    char arr[] = "hello";

    func1(arr);
    return 0;
}