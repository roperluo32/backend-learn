#include<iostream>
#include<stack>

using namespace std;

int xiaoxiaole(string s) {
    stack<int> st;
    for(char c : s) {
        int num = c - '0';
        if (st.empty()) {
            st.push(num);
            continue;
        }

        if (st.top() + num == 10) {
            st.pop();
        } else {
            st.push(num);
        }
    }

    return st.size();
}

int main() {
    string s = "213792";
    cout << xiaoxiaole(s) << endl;
}