#include <iostream>
#include <memory>

class A {
    int* a = 0;
public:
    A() {
        a = new int(0);
        std::cout << "default A()" << std::endl;
    }
    A(int a1):a(new int(a1)) {
        std::cout << "A(int): " << *a << std::endl;
    }
    // A(int* a_):a(a_) {
    //     if (a != nullptr) {
    //         delete a;
    //         a = a_;
    //     }
    //     std::cout << "A(int*)" << std::endl;
    // }
    A(A&& oth):a(oth.a) {
        oth.a = nullptr;
        std::cout << "A(&&)" << std::endl;
    }
    A(const A&oth) {
        a = new int(*oth.a);
        std::cout << "A(const &)" << std::endl;
    }

    ~A() {
        delete a;
        std::cout << "~A()" << std::endl;
    }

    A& operator=(A&& oth) {
        std::cout << "operator&&=" << std::endl;
        if (&oth != this) {
           this->a = oth.a;
           oth.a = nullptr;
        }
        return *this;
    }

    A& operator=(A& oth) {
        std::cout << "deep operator=" << std::endl;
        if (&oth != this) {
           *(this->a) = *(oth.a);
        }
        return *this;
    }

    int get_value() {
        return *a;
    }
};

struct delete_array {
    void operator()(A* p) {
        delete[] p;
    }
};

int main() {
    {
        std::unique_ptr<A,delete_array> up1(new A[10]);
        // std::unique_ptr<A> up2 = std::move(up1);

        std::cout << "up1: " << up1.get() << std::endl;
        // std::cout << "up2: " << up2.get() << std::endl;

        // auto A1 = new A(20);
        // auto A2 = A1;
        // A A1(3);
        // A A2 = A1;
        // A A3 = std::move(A1);
        // auto& A2 = A1;
        // A A5(4);
        // A5 = A1;
        // A5 = std::move(A1);
        // std::cout << A1->get_value() << ", " << A2->get_value() << std::endl;
    }


    return 0;
}