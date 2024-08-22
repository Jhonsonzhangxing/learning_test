#include <iostream>
#include <concept>

// template<typename T>
// concept Integral = std::is_integral<T>::value;

// Intergral auto gcd(Integral auto a, Integral auto b) {
//   if (b == 0) return a;
//   else return gcd(b, a % b);
// }



// int main() {
//     std::cout << gcd(10,5) << std::endl;
// }

//  #include <concepts>
//  #include <iostream>
 
//  template<std::integral... Args>
//  bool all(Args... args) { return (... && args); }
 
//  template<std::integral... Args>
//  bool any(Args... args) { return (... || args); }
 
//  template<std::integral... Args>
//  bool none(Args... args) { return not(... || args); }
 
//  int main() {
 
//      std::cout << std::boolalpha << '\n';
 
//      std::cout << "all(5, true, false): " << all(5, 5, 5) << '\n';
 
//      std::cout << "any(5, true, false): " << any(5, false, false) << '\n';
 
//      std::cout << "none(5, true, false): " << none(false, false, false) << '\n';
 
//  }

 #include <forward_list>
 #include <list>
 #include <vector>

 template<std::forward_iterator I>
 void advance(I&iter, int n) {
  std::cout << "forward_iterator.." << std::endl;
 }

 template<std::bindirectional_iterator I>
 void advance(T&iter, int n) {
  std::cout << "bidirectional_iterator" << std::endl;
 }

template<std::random_access_iterator I>
 void advance(T&iter, int n) {
  std::cout << "random_access_iterator" << std::endl;
 }

int main() {
  std::forward_list forwalist{1,2,3,4};
  std::forward_list<int>::iterator itr = forwalist.begin();
  advance(itr,2);

  std::list li{1,2,3};
  std::list<int>::iterator it = li.begin();
  advance(it,2);

  std::vector vec{1,2,3};
  std::vector<int>::iterator itR = vec.begin();
  advance(itR,2);k

}