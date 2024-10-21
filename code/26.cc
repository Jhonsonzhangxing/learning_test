#include <iostream>
#include <vector>

void rmdup(std::vector<int>& vec, int val) {
    int k = 0;
    for (int i = 0; i < vec.size(); ++i) {
        if (k==0 || vec[i] != val) {
            vec[k++] = val;
        }
    }
}

int main() {

    return 0;
}