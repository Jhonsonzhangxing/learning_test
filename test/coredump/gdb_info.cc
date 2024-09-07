#include <iostream>
#include <vector>
#include <array>

const int SUM = 9;
void fun(std::vector<int>& vec,std::vector<int>& vec1,std::array<int,3>& arr) {
    vec.erase(vec.begin());
    vec.erase(vec.begin());
    vec.erase(vec.begin());
    vec.erase(vec.begin());
}

int main() {
    std::vector<int> vec = {1,2,3};
    std::vector<int> vec1 = {4,5,6};
    std::array<int,3> arr = {7,8,9};
    std::cout << vec.size() << " -- " << vec1.size() << std::endl;
    fun(vec,vec1,arr);

    return 0;
}