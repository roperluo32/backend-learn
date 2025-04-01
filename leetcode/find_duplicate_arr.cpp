
#include <vector>
#include <iostream>

using namespace std;

vector<int> findDuplicates(vector<int>& nums) {
    vector<int> dups;
    for(int i = 0; i < nums.size(); i++) {
        int idx = abs(nums[i]) - 1;
        if (nums[idx] < 0) {
            dups.push_back(abs(nums[i]));
        } else {
            nums[idx] *= -1;
        }
        
    }

    return dups;
}


int main() {
    vector<int> arr = {1, 2, 2, 3, 4, 5, 5, 6};
    vector<int> result = findDuplicates(arr);
    
    for (int num : result) {
        cout << num << endl;
    }
}