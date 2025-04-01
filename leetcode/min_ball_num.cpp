
// 给定无限个不同重量的金属球和一个总重量，求可以凑成总重量所需的最少球的个数， 如果凑不成返回-1,例如：
// 输入：ball_weights = [1, 2 , 5],  amount=11
// 输出：3          11=5+5+1


#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int helper(vector<int>& weights, int amount, unordered_map<int, int>& dp) {
    if (dp.count(amount) > 0) return dp[amount];
    int minNum = INT_MAX;
    for (int i = weights.size() - 1; i >= 0; i--)
    {
        if (weights[i] > amount) continue;
        if (weights[i] == amount) return 1;
        minNum =  min(minNum, 1 + helper(weights, amount - weights[i], dp));
    }
    if (minNum != INT_MAX) {
        dp[amount] = minNum;
        return minNum;
    }

    return INT_MAX;
}

int calMinBall(vector<int> weights, int amount) {
    unordered_map<int, int> dp;

    return helper(weights, amount, dp);
} 

int main() {
    vector<int> weights = {1,2,5};

    cout << calMinBall(weights, 11) << endl;
}