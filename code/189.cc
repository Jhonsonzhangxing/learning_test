#include <iostream>
#include <vector>
#include <numric>

void reverse(std::vector<int>& vec, int k) {
    k %= vec.size();
    reverse(vec.begin(),vec.end());
    reverse(vec.begin(),vec.begin()+k);
    reverse(vec.begin()+k,vec.end());
}

int main() {

    return 0;
}