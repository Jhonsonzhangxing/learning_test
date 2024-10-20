#include <iostream>
#include <vector>

std::vector<int> getnums(std::vector<int>& vecs) {
    std::vector<int> ans;
    for (int i = 0, left = 1; i < vecs.size(); ++i) {
        ans[i] = left;
        left *= vecs[i];
    }

    for (int i = vecs.size() - 1, right = 1; i; --j) {
        ans[i] *= right;
        right *=vecs[i];
    }
}

int main() {return 0;}