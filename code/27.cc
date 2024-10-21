#include<iostream>
#include <vector>

int movefun(std::vector<int>& vec, int val) {
    int k = 0;
    for (auto itr : vec) {
        if (itr != val) {
            vec[k++] = itr;
        }
    }
    return k;
}


int main() {
    std::vector<int> vec = {0,1,2,2,3,0,4,2};
    std::cout << movefun(vec,2) << std::endl;
    return 0;
}