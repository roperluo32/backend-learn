// 给出一个正整数组成的无序数组nums，返回其中元素组成的最长序列的长度。
// 算法需要再O(n)的时间复杂度内完成。

// 例1：
// 输入：nums = [100, 4, 200, 1, 3, 2]
// 输出：4
// 解释：最常的连续序列为 [1, 2, 3, 4]，所以长度为4

// 例2：
// 输入：nums = [0, 3, 7, 2, 5, 8, 4, 6, 0, 1]
// 输出：9


#include<iostream>
#include<vector>
#include<unordered_map>

using namespace std;

int findLongestSubArr(vector<int> nums) {
    unordered_map<int, int> num_map;

    for (int num : nums) {
        num_map[num] = 1;
    }

    int longest_len = 0;
    for (int num: nums) {
        if (num_map.count(num+1) > 0) {
            continue;
        }

        int n = num - 1;
        int len = 1;
        while (num_map.count(n) > 0) {
            len += 1;
            n--;
        }
        longest_len = max(longest_len, len);
    }

    return longest_len;
}

int main() {
    // vector<int> nums = {0, 3, 7, 2, 5, 8, 4, 6, 0, 1};
    vector<int> nums = {100, 4, 200, 1, 3, 2};
    cout << findLongestSubArr(nums) << endl;
}