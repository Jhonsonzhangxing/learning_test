#include <iostream>
#include <vector>

int maxprice(std::vector<int>& vec) {
    int n = vec.size();
    int f[n][2];
    f[0][1] = 0;
    f[0][0] = -vec[0];

    for (int i = 1; i < n; ++i) {
        f[i][0] = std::max(f[i-1][0],f[i-1][1]-vec[i]);
        f[i][1] = std::max(f[i-1][1],f[i-1][0]+vec[i]);
    }
    return f[n-1][1];
}


int main() {

    return 0;
}
