// 根据一棵树的中序遍历与后序遍历构造二叉树。
// 注意:
// 你可以假设树中没有重复的元素。
// 例如，给出
// 中序遍历 inorder = [9,3,15,20,7]
// 后序遍历 postorder = [9,15,7,20,3]

#include<iostream>
#include<vector>
#include<unordered_map>

using namespace std;

struct TreeNode {
    int value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int v): value(v), left(nullptr), right(nullptr) {}
};


TreeNode* buildHelper(vector<int> inorder, vector<int> postorder, int inStart, int inEnd, int postStart, int postEnd, unordered_map<int, int>& inmap) {
    if (inStart >= inEnd || postStart >= postEnd) 
        return nullptr;

    int rootValue = postorder[postEnd];
    int rootInIdx = inmap[rootValue];

    int leftNodeNum = rootInIdx - inStart;

    TreeNode* newNode = new TreeNode(rootValue);

    newNode->left = buildHelper(inorder, postorder, inStart, rootInIdx-1, postStart, postStart+leftNodeNum-1, inmap);
    newNode->right = buildHelper(inorder, postorder, rootInIdx+1, inEnd, postStart+leftNodeNum, postEnd-1, inmap);

    return newNode;
}

TreeNode* buildTree(vector<int> inorder, vector<int> postorder) {
    
    unordered_map<int, int> inMap;

    for (int i = 0; i < inorder.size(); i++) {
        inMap[inorder[i]] = i;
    }

    return buildHelper(inorder, postorder, 0, inorder.size()-1, 0, postorder.size()-1, inMap);
}

int main() {
    vector<int> inorder = {9, 3, 15, 20, 7};
    vector<int> postorder = {9, 15, 7, 20, 3};

    buildTree(inorder, postorder);
}