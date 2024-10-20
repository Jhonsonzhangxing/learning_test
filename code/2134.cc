#include <iostream>
#include <vector>

#include <algorithm>
#include <numeric>
// 最少交换次数来组合所有的 1 II

int minnum (std::vector<int>& vec) {
    int k = accumulate(vec.begin(),vec.end(),0);
    int tmp = accumulate(vec.begin(),vec.begin()+k, 0);
    int n  = vec.size();
    int mx = tmp;
    for (int i = 1; i < n; ++i) {
        tmp += vec[(i+k-1)%n] - vec[i%n];
        mx = std::max(mx,tmp);
    }
    return k - mx;
}

int main() {
    std::vector<int> vec = {0,1,1,1,0,0,1,1,0};
    std::cout << minnum(vec) << std::endl;
    return 0;
}
