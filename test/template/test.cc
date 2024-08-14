#include <iostream>

template <typename T>
bool equivalent(const T& a, const T& b) { 
    static int count;
    std::cout << "count: " << ++count << std::endl;
    return !(a < b) && !(b < a); }

template <typename T = int>
class bignumber {
    T v_;
public:
    bignumber(T v) : v_(v){};
    inline bool operator<(const bignumber& b) const;
};

template <typename T>
bool bignumber<T>::operator<(const bignumber& b) const {
    return v_ < b.v_;
}

// //模板特化
// template <typename T, int N>
// class Vec {
//     T v_[N];
// };

// template<>
// class Vec<float, 4> {
//     float v_[4];
// };

// template <int N>
// class Vec<bool, N> {
//     char v_[(N+sizeof(char)-1)/sizeof(char)];
// };

//模板特例化
template<typename T, int i>class cp00;
//通例
template<typename T1, typename T2,int i, template<typename, int> class CP>
class TMP;

//完全特例化
template<>
class TMP<int, float, 2, cp00>;

//第一个有const 修饰
template<typename T1, typename T2, int i, template<typename,int> class CP>
class TMP<const T1, T2,i,CP>;

template<typename T, int i>
class TMP<cp00<T,i>,cp00<T,i+10>,i,cp00>;

//识别两个类型是否相同
template<typename T1, typename T2>
class theSameType {public:enum {ret = false};};

template<typename T>
class theSameType<T,T>{public: enum{ret = true};};
template<typename T, int i> class aTMP{};

template<typename T>
class aTMP1 {
public: 
    void f1() {std::cout << "f1()\n" << std::endl;}
    void f2() {std::cout << "f2()\n" << std::endl;}
};

template<int N>
class aTMP2 {
    public:
    enum{ret = N * aTMP2<N-1>::ret};
};

template<>
class aTMP2<0> {
    public:
    enum{ret = 1};
};
template<typename T>
class aTMP3 {
    public:
    typedef const T reType;
};

void f() {std::cout << "global f()" << std::endl;}

template<typename T>
class Base {
    public:
    template <int N = 99>
    void f() {std::cout << "member f(): " << N  << std::endl;}
};

template<typename T>
class Derived : public Base<T> {
    public:
    typename T::reType m;
    Derived(typename T::reType a):m(a) {}
    void df1() {f();}
    void df2() {this->template f();}
    void df3() {Base<T>::template f<22>();}
    void df4() {::f();}
};


// 通例为空，若不匹配特例将报错，很好的调试手段（这里是 bool 就无所谓了）
template<bool c, typename Then, typename Else> class IF_{};
template<typename Then, typename Else>
class IF_<true, Then, Else> {public: typedef Then reType;};
template<typename Then, typename Else>
class IF_<false, Then, Else> {public: typedef Then reType;};


template<template<typename> class Condition, typename Statement>
class WHILE_ {
    template<typename Statement1> class STOP {public: typedef Statement1 reType;};
public:
    typedef typename 
        IF_<Condition<Statement>::ret,
            WHILE_<Condition,typename Statement::Next>,
            STOP<Statement>>::reType::reType
        reType;
};

int lcm(int a, int b){
    int r, lcm=a*b;
    std::cout << "lcm: " << lcm << ", a: " << a << ", b: " << b <<std::endl;
    while(r=a%b) { 
        std::cout << "r=a%b: " << r  << ", a: " << a << ",b: " << b <<std::endl;
        a = b; 
        b = r; 
        } // 因为用可变的存储，不能写成 a=b; b=a%b;
    std::cout << "r=a%b: " << r  << ", a: " << a << ",b: " << b <<std::endl;
    return lcm/b;
}

template<int n, int e>
class sum_pow {
    template<int i, int e1> class pow_e{public: enum{ret=i*pow_e<i,e-1>::ret};};
    template<int i> class pow_e<i,0>{public: enum{ret=1};};
    template<int i> class pow{public: enum{ret= pow_e<i,e>::ret};};
    template<typename stat> 
    class cond {public:enum{ret=(stat::ri<=n)};};
    template<int i,int sum>
    class stat {public:typedef stat<i+1,sum+pow<i>::ret> Next;
                enum{ri=i,ret=sum};};
public:
    enum{ret=WHILE_<cond,stat<1,0>>::reType::ret};
};

template<int a, int b>
class lcm_T {
    template<typename stat>
    class cond{public:enum{ret=(stat::div!=0)};};
    template<int a1, int b1>
    class stat{public:typedef stat<b1,a1%b1> Next; enum{div=a1%b1,ret=b1};};
    static const int gcd=WHILE_<cond,stat<a,b>>::reType::ret;
public:
    static const int ret=a*b/gcd;
};

#include <iostream> // std::cout
#include <cmath>    // std::sqrt()

// // 表达式类型
// class DExprLiteral {                    // 文字量
//     double a_;
// public:
//     DExprLiteral(double a) : a_(a) { }
//     double operator()(double x) const { return a_; }
// };
// class DExprIdentity {                   // 自变量
// public:
//     double operator()(double x) const { return x; }
// };
// template<class A, class B, class Op>    // 双目操作
// class DBinExprOp {
//     A a_; B b_;
// public:
//     DBinExprOp(const A& a, const B& b) : a_(a), b_(b) { }
//     double operator()(double x) const { return Op::apply(a_(x), b_(x)); }
// };
// template<class A, class Op>             // 单目操作
// class DUnaryExprOp {
//     A a_;
// public:
//     DUnaryExprOp(const A& a) : a_(a) { }
//     double operator()(double x) const { return Op::apply(a_(x)); }
// };
// // 表达式
// template<class A>
// class DExpr {
//     A a_;
// public:
//     DExpr() { }
//     DExpr(const A& a) : a_(a) { }
//     double operator()(double x) const { return a_(x); }
// };

// // 运算符，模板参数 A、B 为参与运算的表达式类型
// // operator /, division
// class DApDiv { public: static double apply(double a, double b) { return a / b; } };
// template<class A, class B> DExpr<DBinExprOp<DExpr<A>, DExpr<B>, DApDiv> >
// operator/(const DExpr<A>& a, const DExpr<B>& b) {
//     typedef DBinExprOp<DExpr<A>, DExpr<B>, DApDiv> ExprT;
//     return DExpr<ExprT>(ExprT(a, b));
// }
// // operator +, addition
// class DApAdd { public: static double apply(double a, double b) { return a + b; } };
// template<class A, class B> DExpr<DBinExprOp<DExpr<A>, DExpr<B>, DApAdd> >
// operator+(const DExpr<A>& a, const DExpr<B>& b) {
//     typedef DBinExprOp<DExpr<A>, DExpr<B>, DApAdd> ExprT;
//     return DExpr<ExprT>(ExprT(a, b));
// }
// // sqrt(), square rooting
// class DApSqrt { public: static double apply(double a) { return std::sqrt(a); } };
// template<class A> DExpr<DUnaryExprOp<DExpr<A>, DApSqrt> >
// sqrt(const DExpr<A>& a) {
//     typedef DUnaryExprOp<DExpr<A>, DApSqrt> ExprT;
//     return DExpr<ExprT>(ExprT(a));
// }
// // operator-, negative sign
// class DApNeg { public: static double apply(double a) { return -a; } };
// template<class A> DExpr<DUnaryExprOp<DExpr<A>, DApNeg> >
// operator-(const DExpr<A>& a) {
//     typedef DUnaryExprOp<DExpr<A>, DApNeg> ExprT;
//     return DExpr<ExprT>(ExprT(a));
// }

// // evaluate()
// template<class Expr>
// void evaluate(const DExpr<Expr>& expr, double start, double end, double step) {
//     for(double i=start; i<end; i+=step) std::cout << expr(i) << ' ';
// }
#include <vector>

template <char...C>
struct Symbol {
    static const char value[sizeof...(C)+1]= {C...,'\0'};
};


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

template <typename E>
class VecExpr {
public:
    double operator[] (int i) const {return static_cast<E const&>(*this)[i];}
    operator E const&() const {return static_cast<const E&>(*this);}
};

class Vec:public VecExpr<Vec> {
    double _data[1000];
public:
    double& operator[] (int i){return _data[i];}
    double operator[] (int i)const {return _data[i];}
    template <typename E>
    Vec const& operator=(VecExpr<E> const& vec) {
        E const& v = vec;
        for (int i = 0; i < 1000; ++i) _data[i] = v[i];
        return *this;
    }

    Vec() {}
    Vec(double v) { for (int i = 0; i < 1000; ++i)  _data[i] = v; }
};

template <typename E1, typename E2>
class VecDifference : public VecExpr<VecDifference<E1,E2>> {
    E1 const& _u;E2 const& _v;
public:
    VecDifference(VecExpr<E1> const& u, VecExpr<E2> const& v):_u(u),_v(v) {}
    double operator[](int i) const {return _u[i] - _v[i];}
};

template <typename E>
class VecScaled: public VecExpr<VecScaled<E>> {
    double _alpha; E const& _v;
public:
    VecScaled(double alpha, VecExpr<E> const& v): _alpha(alpha), _v(v) {}
    double operator[](int i)const {return _alpha*_v[i];}
};

template <typename E1, typename E2> VecDifference<E1,E2> const
operator-(VecExpr<E1> const& u, VecExpr<E2> const& v) {
    return VecDifference<E1,E2>(u,v);
}

template<typename E> VecScaled<E> const
operator*(double alpha, VecExpr<E> const& v) {
    return VecScaled<E>(alpha,v);
}

// class OpAdd
template<typename T1, typename T2, typename F>
T1 OperatorSet (const T1& a, const T2& b, F f) {
    return f(a,b);
    // switch (op)
    // case:
    // case:
}


template <typename T, typename U = typename std::enable_if<std::is_integral<T>::value, T>::type>
void printIntegral(T value) {
    std::cout << value << std::endl;
}

template <typename T = int, typename... Args>
void variadicFunc(T a, Args... args) {
    std::cout << "a= " << a << std::endl;
    ((std::cout << "arg= " << args << " "),...);
    std::cout << std::endl;
}

template <typename T, typename Compare = std::less<T>>
bool myCompare(const T& a, const T& b) {
    Compare comp;
    return comp(a, b);
}


#include <iterator>
template <typename T, typename Printer = typename std::ostream_iterator<T>>
void printElements(std::ostream& os, const std::initializer_list<T>& list, const std::string& sep = ", ") {
    std::copy(list.begin(),list.end(),Printer(os, sep.c_str()));
}

template <typename T = int>
class Base1 {
public:
    void doSomething(T value) {
        std::cout << "Base::doSomething: " << value << std::endl;
    }
};

template <typename U = double, typename T = U>
class Derived1 : public Base1<T> {
public:
    void doSomething(U value) {
        std::cout << "Derived::doSomething: " << value << std::endl;
        Base1<T>::doSomething(value);
    }
};
#include <vector>
#include <string>
#include <algorithm>
template <typename Container, typename Iterator = typename Container::iterator>
void reverseContainer(Container& c) {
    std::reverse(c.begin(), c.end());
}
#include <functional>
template <typename Container, typename T, typename Finder = std::find<typename Container::const_iterator, T>>
typename Container::size_type findInContainer(const Container& c, const T& value) {
    auto it = Finder(std::begin(c), std::end(c), value);
    return it  = std::end(c) ? Container::npos : std::distance(std::begin(c), it);
}


int main() {
    std::vector<int> v = {1,2,3,4,5};
    reverseContainer(v);
    std::string str("hello");
    reverseContainer(str);
    std::cout << str << std::endl;

    // Derived1<> d;
    // d.doSomething(1.2);
    // Derived1<int> d;
    // d.doSomething(1.2);
    // printElements(std::cout, {1,2,3}, " | ");
    // std::cout << myCompare(3,5) << std::endl;
    // variadicFunc(1,2,3,"adc",5);
    // std::cout << theSameType< std::vector<int>::iterator::iterator_category,
    //                           std::random_access_iterator_tag >::ret << '\n';
    // std::cin.get(); 
    // Symbol("hello");
    // std::cout << "Hello, World! : " << OperatorSet(1,2,Add<int,int>) <<  std::endl;
    // Vec u(3),v(1); double alpha=9; Vec y;
    // // y = alpha*(u-v);
    // y = u-v;
    // std::cout << y[999] << std::endl;

    return 0;
}

// int main() {
//     // bignumber<> a(1), b(1);
//     // std::cout << equivalent(a, b) << std::endl;
//     // std::cout << equivalent<double>(1,2) << std::endl;
//     // typedef unsigned int uint;
//     // typedef uint uint2;
//     // std::cout << theSameType<unsigned, uint2>::ret << std::endl;
//     // std::cout << theSameType<aTMP<unsigned,2>,aTMP<uint2,2>>::ret << std::endl;
//     // std::cout << theSameType<aTMP<int,2>,aTMP<int,2>>::ret << std::endl;
//     // aTMP1<int> a;
//     // std::cout << aTMP2<10>::ret <<std::endl;
//     // Derived<aTMP3<int>> a(10);
//     // a.df1();
//     // a.df2();
//     // a.df3();
//     // a.df4();
//     // const int len = 4;
//     // typedef
//     //     IF_<sizeof(short)==len, short,
//     //     IF_<sizeof(int)==len, int,
//     //     IF_<sizeof(long)==len, long,
//     //     IF_<sizeof(long long)==len, long long,
//     //     void>::reType>::reType>::reType>::reType
//     // int_my; // 定义一个指定字节数的类型
//     //     typedef
//     //     IF_<sizeof(short)==len, short, IF_<sizeof(int)==len, int, void>::reType>::reType
//     // int_my; // 定义一个指定字节数的类型   
//     // std::cout << sizeof(int_my) << '\n';
//     // std::cout << "..." << std::endl;
//     // std::cout << sizeof(short) << std::endl;
//     // std::cout << sizeof(int) << std::endl;
//     // std::cout << sizeof(long) << std::endl;
//     // std::cout << sizeof(long long) << std::endl;

//     lcm(2,3);

//     return 0;
// }