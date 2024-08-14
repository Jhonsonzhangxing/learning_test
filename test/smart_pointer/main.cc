#include <iostream>
#include <memory>
 
struct Foo
{
    int id;
    Foo(int id) : id(id) { std::cout << "Foo " << id << '\n'; }
    ~Foo() { std::cout << "~Foo " << id << '\n'; }
    int  test() {
        std::cout << "test" << std::endl;
        return id;
    }
};
 
int main() 
{
    // std::unique_ptr<Foo> p1(std::make_unique<Foo>(1));
    // {
    //     std::cout << "创建新的 Foo...\n";
    //     std::unique_ptr<Foo> p2(std::make_unique<Foo>(2));
    //     // p1 = p2; // 错误！不能复制 unique_ptr
    //     // p1 = std::move(p2);
    //     p1 = nullptr;
    //     std::cout << "准备离开内层块...id: " << p1->test() << std::endl;
    //     // 即使 p2 将要离开作用域，但是 Foo 示例会继续生存
    // }
 
    // std::cout << "准备离开程序...\n";
    std::shared_ptr<int> sPtr1 = std::make_shared<int>(1);
    std::shared_ptr<int> sPtr2 = sPtr1;

    return 0;
}