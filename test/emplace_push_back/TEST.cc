/*
给定一个长度为 n 的数组 num 和滑动窗口的大小 size ，找出所有滑动窗口里数值的最大值。
例如，如果输入数组{2,3,4,2,6,2,5,1}及滑动窗口的大小3，那么一共存在6个滑动窗口，他们的最大值分别为{4,4,6,6,6,5}；
针对数组{2,3,4,2,6,2,5,1}的滑动窗口有以下6个： {[2,3,4],2,6,2,5,1}， {2,[3,4,2],6,2,5,1}， {2,3,[4,2,6],2,5,1}， {2,3,4,[2,6,2],5,1}，
{2,3,4,2,[6,2,5],1}， {2,3,4,2,6,[2,5,1]}。
窗口大于数组长度或窗口长度为0的时候，返回空。
数据范围： 1≤n≤10000，0≤size≤10000，数组中每个元素的值满足 ∣val∣≤10000∣
要求：空间复杂度 O(n)，时间复杂度 O(n)
示例1
输入：
[2,3,4,2,6,2,5,1],3
返回值：
[4,4,6,6,6,5]

示例2
输入：
[9,10,9,-7,-3,8,2,-6],5
返回值：
[10,10,9,8]

示例3
输入：
[1,2,3,4],5
返回值：
[]
*/

#include<iostream>
#include<vector>
#include<deque>
using namespace std;

std::vector<int> MaxNumInWindow(const std::vector<int>& nums, int wid_num) {
    std::vector<int> ret_vec;
    if (nums.empty() || nums.size() < wid_num) return ret_vec;
    
    for (int i = 0; i < nums.size() - wid_num; ++i) {
        int max = nums[i];
        for (int j = i+1; j < wid_num; ++j) {
            if(max < nums[j]) {
                max = nums[j];
            }
        }
        ret_vec.push_back(std::move(max));
    }
    return ret_vec;
}


int main() {
    std::vector<int> nums = {2,3,4,2,6,2,5,1};


}