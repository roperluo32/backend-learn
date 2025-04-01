// 给定一个整数数组 nums ，找到一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int maxSubArray(vector<int>& nums) {
    if (nums.size() == 0) { return 0; }

    int curMax = nums[0];
    int allMax = nums[0];

    for (int i = 0; i < nums.size(); i++) {
        curMax = max(curMax + nums[i], nums[i]);
        allMax = max(curMax,  allMax);
    }

    return allMax;
}

int main() {

    vector<int> nums = {-2,1,-3,4,-1,2,1,-5,4};
    int res = maxSubArray(nums);

    cout << res << endl;
}