#include <iostream>
#include <vector>

int minwindow(std::vector<int>& vec, int val) {
    int l = 0, r = 0, ans = vec.size() + 1;
    long long s;
    
    for (; r < vec.size(); ++r) {
        s += vec[r];
        while (s >= val) {
            ans = std::min(ans,r-l+1);
            s-=vec[l++];
        }
    }
    return ans - vec.size() > 0 ? 0 : 1;

}
