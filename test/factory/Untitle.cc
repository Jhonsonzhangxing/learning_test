#include <iostream>
#include <vector>
#include <memory>
enum type {
    UNKOWN = 0,
    G9_t = 1,
    P7i_t = 2,
    P5_t = 3,
};

class Car {
public:
    Car() {
        std::cout << "Car constructor" << std::endl;
    }

    virtual void Move(){};
    virtual ~Car() {
        std::cout << "Car destructor" << std::endl;
    }
};

class G9 :public Car {
    type m_type = type::G9_t;
public:
    G9() {
        std::cout << "G9 constructor" << std::endl;
    }
    virtual ~G9() {
        std::cout << "G9 destructor" << std::endl;
    }

    void Move()  {
        std::cout << "G9 Move" << std::endl;
    }

};

class P7i :public Car {
    type m_type = type::P7i_t;
public:
    P7i() {
        std::cout << "P7i constructor" << std::endl;
    }
    virtual ~P7i() {
        std::cout << "P7i destructor" << std::endl;
    }

    void Move()  {
        std::cout << "P7i Move" << std::endl;
    }
    
};

class P5 :public Car {
    type m_type = type::P5_t;
public:
    P5() {
        std::cout << "P5 constructor" << std::endl;
    }
    virtual ~P5() {
        std::cout << "P5 destructor" << std::endl;
    }

    void Move()  {
        std::cout << "P5 Move" << std::endl;
    }
};


class Factory {
public:
    Car* CreateCar(type t) {
        switch (t) {
            case type::G9_t:
                return new G9();
            case type::P7i_t:
                return new P7i();
            case type::P5_t:
                return new P5();
            default:
                return nullptr;
        }
    }
    ~Factory() {}
};

int main() {
    {
        Factory f;
        std::unique_ptr<Factory> factory(new Factory());
        std::unique_ptr<Car> G9_prt(factory->CreateCar(type::G9_t));
        G9_prt->Move();
    }

    
    while(1) std::cin.get();

    return 0;
}