#include <iostream>
using namespace std;
class Base {
    int a = 1;
public:
    Base() {
        cout << "Base()" << endl;
    }

    ~Base() {
        cout << "~Base()" << endl;
    }
    void b() {

    }
};

class Derived : public Base {
    int b = 2;
public:
    Derived() {
        cout << "Derived()" << endl;
    }

    ~Derived() {
        cout << "~Derived()" << endl;
    }
    void d() {
        ;
    }
};

int main() {
    // Base *b1 = new Derived;
    // b1->b();
    // delete b1;
    // cout << endl;
    {
        Derived d;
        Base &b2 =d;
        // b2.~Base();
    }

    return 0;
}
