#include <iostream>
#include <vector>

bool isreach(std::vector<int>& vec) {
    int k = 0;
    for (int i = 0; i < vec.size(); ++i) {
        if(k < i) return false;
        k = std::max(k,i+vec[i]);
    }
    return true;
}
