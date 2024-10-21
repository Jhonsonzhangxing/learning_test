#include <iostream>
#include <vector>

void merge(std::vector<int>& num1, int m, std::vector<int>&num2, int n) { 
    for (int i = m - 1, j = n -1, k = m+n-1; ~j; --k) {
        num1[k] = i >= 0 && num1[i] > num2[j] ? num1[i--] : num2[j--];
    }
}


int main() {
    std::vector<int> nums1 = {1,2,3,0,0,0}, nums2 = {2,5,6};
    merge(nums1,3,nums2,3);
    return 0;
}