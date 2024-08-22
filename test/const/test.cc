#include <iostream>
#include <vector>
void func(const char*& Var){
    
    Var = "Hello";
    std::cout << &Var  << ", value: " << Var << " ,*Var: " << *Var<< std::endl;
    }
void func1(char* const Var) {
    // Var = "Hello";
    *Var = 'H';
    // Var++;
}

class Tem {
    public:
    Tem(){ std::cout << "construct" << std::endl;}
    Tem(const Tem& oth) {std::cout << "copy-construct" << std::endl;}
    const Tem& operator=(const Tem& oth) {std::cout << "copy-assign" << std::endl; return static_cast<const Tem&> (*this);}
    
    ~Tem() {};
private:
    const int i = 1;
};





int main() {
    const int n = 10;
    // n = 11;

    int i = 10;
    int * const p = &i;
    // p++;
    *p = 20;

    int const* p2 = &i;
    const int* p3 = &i;
    p2++;
    p3++;

    int const* const p4 = &i;

    char* a = "a";
    std::cout << "a: " << a << ", *a: " << *a<< std::endl;
    int aa = 1;
    const int* a1 = &aa;
    // *a1 = 2;
  
    char* tmp = "abc";
    const char* Var = tmp;
    std::cout << &Var  << ", value: " << Var  << ",*Var: " << *Var << std::endl;
    // *Var = "test";
    func(Var);
    std::cout << Var << std::endl;



    return 0;
}