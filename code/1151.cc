#include <iostream>
#include <vector>

int minSwaps(std::vector<int>& vecs) {
    int num = 0;
    for(auto itr : vecs) {
        if (itr == 1) {
            ++num;
        }
    }

    int tmp = 0;
    for (int i = 0; i < num; ++i) {
        if (vecs[i] == 1) {
            tmp++;
        }
    }

    int min = tmp;
    for (int i = num; i < vecs.size(); ++i) {
        if(vecs[i] == 1) tmp++;
        if(vecs[i-num] == 1) tmp--;
        if (min < tmp) min = tmp;
    }
    return min;
}


int main() {
    std::vector<int> vec={1,0,1,0,1,0,0,1,1,0,1};
    std::cout << minSwaps(vec) << std::endl;
    return 0;
}