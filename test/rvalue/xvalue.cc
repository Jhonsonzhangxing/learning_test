#include <iostream>
using namespace std;
// class shape {
// public:
//     shape() { cout << "shape" << endl; }

//     virtual ~shape() {
//         cout << "~shape" << endl;
//     }
// };
// class circle : public shape {
// public:
//     circle() { cout << "circle" << endl; }


//     ~circle() {
//         cout << "~circle" << endl;
//     }
// };
// class triangle : public shape {
// public:
//     triangle() { cout << "triangle" << endl; }


//     ~triangle() {
//         cout << "~triangle" << endl;
//     }
// };
// class rectangle : public shape {
// public:
//     rectangle() { cout << "rectangle" << endl; }

//     ~rectangle() {
//         cout << "~rectangle" << endl;
//     }
// };
// class result {
// public:
//     result() { puts("result()"); }

//     ~result() { puts("~result()"); }
// };
// result process_shape(const shape &shape1, const shape &shape2) {
//     puts("process_shape()");
//     return result();
// }
// int main() {
//     // process_shape(circle(), triangle());
    
//     // result&& r = process_shape(circle(), triangle());
   
//     result&& r1 = std::move(process_shape(circle(), triangle()));
//      std::cout << "...................." << std::endl;
// }

// template<typename T>
// class Widget {
//     typedef T& LvalueRefType;
//     typedef T&& RvalueRefType;
// public:
//     void judge() {
//         static_assert(std::is_lvalue_reference<LvalueRefType>::value, "LvalueRefType & is lvalue reference");
//         static_assert(std::is_lvalue_reference<RvalueRefType>::value, "RvalueRefType & is lvalue reference");
//         cout << "LvalueRefType and RvalueRefType is lvalue reference" << endl;
//     }
// };
// int main() {
//     Widget<int&> w;
//     w.judge();
// }


