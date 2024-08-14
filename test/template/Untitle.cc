#include <iostream>

template<typename T1, typename T2>
T1 Add (T1 a, T2 b) {
    return a+b;
}

template<typename T1, typename T2>
T1 Div (T1 a, T2 b) {
    return a/b;
}


enum class Operator {
    Add = 0,
    Div = 1
};

// class OpAdd 

template<typename T1, typename T2, typename F>
T1 OperatorSet (const T1& a, const T2& b, F f) {
    return f(a,b);
    // switch (op)
    // case:
    // case:
}


int main() {
    std::cout << "Hello, World!" << std::endl;

    OperatorSet(1,2,Add<int,int>);
    return 0;
}