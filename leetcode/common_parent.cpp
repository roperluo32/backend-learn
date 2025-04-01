#include<iostream>
#include<unordered_map>

using namespace std;

struct Node {
    Node* left;
    Node* right;
    int value;

    Node(): left(nullptr), right(nullptr) {}
};

void recordParent(Node* node, unordered_map<Node*, Node*>& node_map) {
    if (nullptr == node) return;

    if (node->left) {
        node_map[node->left] = node;
        recordParent(node->left, node_map);
    }

    if (node->right) { 
        node_map[node->right] = node;
        recordParent(node->right, node_map);
    }
}

Node* findCommonParent(Node* root, Node* p, Node* q) {
    unordered_map<Node*, Node*> node_map;

    node_map[root] = nullptr;

    recordParent(root, node_map);

    unordered_map<Node*, int> route;

    while(nullptr != p) {
        route[p] = 1;
        p = node_map[p];
    }

    while(nullptr != q) {
        if (route.count(q) > 0) return q;
        q = node_map[q];
    }

    return nullptr;
}

int main() {

}