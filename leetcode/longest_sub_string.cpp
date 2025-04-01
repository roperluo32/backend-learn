// 给定一个字符串 s ，请你找出其中不含有重复字符的 最长子串 的长度。

#include<iostream>
#include<unordered_map>

using namespace std;

int lengthOfLongestSubstring(string s) {
    unordered_map<char, int> record;
    int left, right = 0;
    int maxLen = 0;
    for (right = 0; right < s.size(); right++) {
        if (record.count(s[right]) == 0) {
            record[s[right]] = right;
            maxLen = max(maxLen, right-left+1);
            continue;
        } else {
            left = record[s[right]] + 1;
        }
    }

    return maxLen;
}

int main() {
    string s = "abcabcefa";

    cout << lengthOfLongestSubstring(s) << endl;
}