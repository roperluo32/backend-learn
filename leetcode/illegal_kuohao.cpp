// 给定一个只包含 "()[]{}" 六种字符的字符串。规定它们的优先级由外至内为："{}", "[]", "()"，同一级的可以嵌套，并列。要求判断给定的字符串是否是合法的括号字串？
// 例："()", "{((()())())[()]}()" 是合法的。"())", "([])", "())(()" 都是不合法的。

#include<iostream>
#include<stack>

using namespace std;

bool isIllegal(string s) {
    stack<char> st;
    for(char c : s) {
        if (c == '{' || c == '(' || c == '[') { 
            st.push(c); 
        } else {
            if (st.empty()) return false;
            char top = st.top();
            if (c == '}' && top != '{') return false;
            if (c == ']' && top != '[') return false;
            if (c == ')' && top != '(') return false;
            st.pop();
        } 
    }
    if (st.empty()) return true;
    return false;
}

int main() {
    string s = "{((()())())[()]}()";

    cout << isIllegal(s) << endl;

    s = "{((()())())[()]()";

    cout << isIllegal(s) << endl;
}