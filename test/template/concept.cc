#include <iostream>
#include <concept>

template<typename T>
concept Integral = std::is_integral<T>::value;

Intergral auto gcd(Integral auto a, Integral auto b) {
  if (b == 0) return a;
  else return gcd(b, a % b);
}



int main() {
    std::cout << gcd(10,5) << std::endl;
}