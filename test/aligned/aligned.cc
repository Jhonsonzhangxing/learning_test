#include<iostream>

#pragma pack(push,1)
struct UnalignedStruct {
    char a;
    int b;
    short c;
};
#pragma pack(pop)

struct AlignedStruct {
    char a;
    int b;
    short c;//(1+3) + 4 + (2+2)
};

struct MyStruct {
    double a;
    char b;
    int c;//(8) + (1+3) + (4)
};

struct MyStruct1 {
    double a;
    char b;
    short c;//(8) + (1+1) + (2) + ((4))
};

struct MyStruct2 {
    char a;
    double b;
    int c;//(8) + (1+1) + (2) + ((4))
};

int main() {
    // std::cout << "size of unaligned struct: " << sizeof(UnalignedStruct) << std::endl;
    // std::cout << "size of aligned struct: " << sizeof(AlignedStruct) << std::endl;
    // std::cout << "size of aligned Mystruct: " << sizeof(MyStruct) << std::endl;
    // std::cout << "size of aligned Mystruct: " << sizeof(MyStruct1) << std::endl;
    // std::cout << "offset a: " << offsetof(MyStruct1,a)  << ", b: " << offsetof(MyStruct1,b) << ", c: " << offsetof(MyStruct1,c) << std::endl;
    std::cout << "size of aligned Mystruct: " << sizeof(MyStruct2) << std::endl;
    std::cout << "offset a: " << offsetof(MyStruct2,a)  << ", b: " << offsetof(MyStruct2,b) << ", c: " << offsetof(MyStruct2,c) << std::endl;
    return 0;
}