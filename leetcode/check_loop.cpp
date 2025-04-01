// 使用引用计数来进行资源管理时，往往需要检测是否存在循环引用
// 假设有n个元素，m个引用关系，每个引用关系(u, v)表示元素u引用了元素v，判断其中是否存在循环引用
// 输入格式如下：
// n m
// u_0 v_0
// ...
// u_(m-1) v_(m-1)
// 输出1或0，表示是否存在循环引用

#include<iostream>
#include<vector>

using namespace std;

bool checkLoop(int node, vector<int> visited, vector<vector<int>> maps) {
    if (visited[node] == 1) return true;   //正在访问中，被重复访问
    if (visited[node] == 2) return false;  // 已经访问过

    visited[node] = 1;
    for(int m: maps[node]) {
        if (checkLoop(m, visited, maps))
            return true;
    }

    visited[node] = 2;
    return false;
}

int main() {
    vector<int> visited;
    vector<vector<int>> maps;

    bool hasLoop = false;
    for(int i = 0; i < visited.size(); i++) {
        if (checkLoop(i, visited, maps)) {
            hasLoop = true;
            break;
        }
    }

    cout << hasLoop << endl;
}