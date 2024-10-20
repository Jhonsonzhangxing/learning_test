
#include<iostream>
#include<vector>
#include<algorithm>

int hIndex(std::vector<int>& citations) {
    sort(citations.rbegin(), citations.rend());
    for (int h = citations.size(); h; --h) {
        if (citations[h - 1] >= h) {
            return h;
        }
    }
    return 0;
}
int main() {
    std::vector<int> vec = {3,0,6,1,5};
    hIndex(vec);
    return 0;
}