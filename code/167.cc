#include <iostream>
#include <vector>
#include <utility>

std::pair<int,int> sum_index(std::vector<int>& vec, int sum) {
    for (int i = 0,j= vec.size()-1;i < j; ) {
        if (vec[i] + vec[j] > sum) {
            j--;
        } else if (vec[i] + vec[j] < sum) {
            i++;
        } else {
            return std::pair<int,int>(i+1,j+1);
        }
    }
}