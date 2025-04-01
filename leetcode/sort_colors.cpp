// 给定一个包含红色、白色和蓝色，一共 n 个元素的数组，原地对它们进行排序，使得相同颜色的元素相邻，并按照红色、白色、蓝色顺序排列。
// 此题中，我们使用整数 0、 1 和 2 分别表示红色、白色和蓝色。

#include<iostream>
#include<vector>

using namespace std;

void sortColors(vector<int>& nums) {
    int left = 0;
    int right = nums.size() - 1;
    int i = 0;
    
    for (int i = 0; i < nums.size(); ) {
        if (left >= i) {
            i++;
            continue;
        }
        if (i > right)
            break;
        if (nums[i] == 0) { 
            swap(nums[left], nums[i]);
            left++;
            continue;
        }
        if (nums[i] == 2) {
            swap(nums[right], nums[i]);
            right--;
            continue;
        }
        
        i++;

    }
}

int main() {
    vector<int> nums = {2, 1, 0, 1, 1, 2, 0, 0, 2, 1};
    sortColors(nums);

    for(int n : nums) cout << n << endl;
}