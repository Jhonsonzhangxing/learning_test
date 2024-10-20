#include <iostream>
#include <vector>

int maxjump(std::vector<int>& vec) {
    int mx = 0, last = 0, cnt = 0;
    for (int i = 0; i < vec.size()-1; ++i) {
        mx = std::max(mx, vec[i] + i);
        if (last = i) {
            cnt++;
            last = mx;
        }
    }

    return ;
}

int main() {
    return 0;
}