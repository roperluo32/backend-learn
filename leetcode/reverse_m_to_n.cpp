

// 单链表内指定区间反转：
// 将一个节点数为size的链表从第m个节点到第n个节点所在的区间节点进行反转
// 链表其他部分不变，返回头节点

#include<iostream>

using namespace std;

struct Node {
    Node* next;
    int value;
};

void reverse(Node* head, int m, int n) {

    int i = 0;
    Node* p = head;

    while (i < m - 1 && p != nullptr) {
        p = p->next;
        i++;
    }

    i = 0;
    Node* pre = p;
    Node* cur = p->next;
    while (pre != nullptr && cur != nullptr && cur->next != nullptr && i < n-m) {

        pre->next = cur->next;
        cur->next = cur->next->next;
        pre->next->next = cur;
        
        cur = pre->next;

        i++;
    }
}