
// 你是一个专业的小偷，计划偷窃沿街的房屋，每间房内都藏有一定的现金。这个地方所有的房屋都围成一圈，这意味着第一个房屋和最后一个房屋是紧挨着的。同时，相邻的房屋装有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警。
// 给定一个代表每个房屋存放金额的非负整数数组，计算你在不触动警报装置的情况下，能够偷窃到的最高金额。

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int robRange(vector<int>& nums, int start, int end) {
    int prev = 0, curr = 0;
    for (int i = start; i <= end; ++i) {
        int temp = max(curr, prev + nums[i]);
        prev = curr;
        curr = temp;
    }
    return curr;
}

int rob(vector<int>& nums) {
    if (nums.empty()) return 0;
    if (nums.size() == 1) return nums[0];
    return max(robRange(nums, 0, nums.size() - 2), robRange(nums, 1, nums.size() - 1));
}

int main() {
    vector<int> nums = {1,2,3,1};
    vector<int> nums1 = {2,3,2};

    cout << rob(nums1) << endl;
}