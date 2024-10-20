#include <iostream>
#include <vector>

int minOperation(std::vector<int>& nums) {
    int index = 0;
    for (int i = 0; i < nums.size(); ++i) {
        if (nums[i] == 1 && index % 2 == 1) ++index;
        if (nums[i] == 0 && index % 2 == 0) ++index;
    }
    return index;
}


int main() {
    std::vector<int> vec={{0,1,0,1,1}};
    std::cout << minOperation(vec) << std::endl;
    return 0;
}