#include <iostream>

#pragma pack(push,1)
struct UnalignedStruct {
    char a;
    int b;
    short c;//1+4+2
};
#pragma pack(pop)

struct myStruct1 {
    char a;
    int b;
    short c;//1+3+4+2+2 = 12
};

struct myStruct2 {
    double a;
    char b;
    int c;//8+1+3+4 = 16
};

struct myStruct3 {
    char a;
    double b;
    int c;//1+7+8+4+4 = 24
};

int main() {
    std::cout << "int: " << sizeof(int) << ", short: " << sizeof(short) << ", double: " << sizeof(double) << std::endl;
    // std::cout << sizeof(UnalignedStruct) << std::endl;
    using myStruct = myStruct3;
    std::cout << sizeof(myStruct) << ",alignof: " << alignof(myStruct) << ", offset a: " << offsetof(myStruct,a) << ",b: " << offsetof(myStruct,b) << ",c: " << offsetof(myStruct, c) << std::endl;
    return 0;
}