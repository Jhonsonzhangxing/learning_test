#include <iostream>
#include <memory>

class A : public std::enable_shared_from_this<A> {
public:
    void func() {
        shared_from_this();
    }
};
 
int main() {
  auto p = std::shared_ptr<int>(new int(4));
  // int num{10};
  // auto p1 = std::shared_ptr<int>(p, &num);
 
  std::weak_ptr<int> wp1 = p;
  
  auto wp2 = wp1;
  
  p = nullptr;

  std::cout << "wp1 use_count: " << wp1.use_count() << std::endl;
            // << "\n" << "p1: " << *p << "\n";
  return 0;
}
