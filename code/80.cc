#include <iostream>
#include <vector>

int rmnum(std::vector<int>& vec, int val) {
    int k = 0;
    for (auto itr : vec) {
        if (k < 2 || itr != vec[k-2]) {
            vec[k++] = itr;
        }
    }
}

int main() {

    return 0;
}