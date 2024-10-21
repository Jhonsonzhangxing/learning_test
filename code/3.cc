#include <iostream>
#include <set>

int minnum(std::string& str) {
    int l = 0,r = 0;
    int ans = 0;
    std::set<char> sets;
    for (;r < str.size(); ++r) {
        while (sets.count(str[r]) && str[l] != str[r]) {
            sets.erase(l++);
        }
        ans = std::max(ans,r-l+1);
        sets.insert(str[r]);
    }
    return ans;
}