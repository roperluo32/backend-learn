// 给定一个数组，它的第 i 个元素是一支给定股票第 i 天的价格。
// 如果你最多只允许完成一笔交易（即买入和卖出一支股票一次），设计一个算法来计算你所能获取的最大利润。

#include<iostream>
#include<vector>

using namespace std;

int maxProfit(vector<int> prices) {
    vector<int> maxs;
    vector<int> mins;

    int max_price = -1;
    int min_price = INT_MAX;
    for(int i = 0; i < prices.size(); i++) {
        if (prices[i] < min_price) min_price = prices[i];
        mins.push_back(min_price);
    }

    for (int i = prices.size() - 1; i >= 0; i--) {
        if (prices[i] > max_price) max_price = prices[i];
        maxs.push_back(max_price);
    }

    int max_result = -1;

    for (int i = 0; i < prices.size(); i++) {
        max_result = max(max_result, maxs[i]-mins[i]);
    }

    return max_result;
}

int main() {
    vector<int> prices = {1, 3, 2, 1, 5, 2, 6};

    int res = maxProfit(prices);

    cout << res << endl;
}