// 给定一个含有 n 个正整数的数组和一个正整数 s ，找出该数组中满足其和 ≥ s 的长度最小的连续子数组，并返回其长度。如果不存在符合条件的子数组，返回 0。

#include <iostream>
#include <vector>

using namespace std;

int minSubArrayLen(int s, vector<int> nums) {
    int left = 0;
    int right = 0;
    int minLen = INT_MAX;
    int curSum = 0;

    for (right = 0; right < nums.size(); right++) {
        curSum += nums[right];

        while(curSum >= s) {
            minLen = min(minLen, right - left + 1);
            curSum -= nums[left];
            left++;
        }
    }

    return minLen == INT_MAX ? 0 : minLen;
}

int main() {
    vector<int> nums1 = {2, 3, 1, 2, 4, 3};
    cout << minSubArrayLen(7, nums1) << endl; // 输出 2
    
    vector<int> nums2 = {1, 4, 4};
    cout << minSubArrayLen(4, nums2) << endl; // 输出 1
    
    vector<int> nums3 = {1, 2, 3, 4, 5};
    cout << minSubArrayLen(11, nums3) << endl; // 输出 3
    
}