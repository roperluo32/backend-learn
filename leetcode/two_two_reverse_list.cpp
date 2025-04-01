

#include<iostream>

using namespace std;

struct Node {
    Node* next;
    int value;
};

void twoReverse(Node* head) {
    Node* p = head;
    Node* q;

    while (p != nullptr && p->next != nullptr) {
        Node* tmp = p->next->next;

        p->next->next = p;
        p->next = tmp;

        p = tmp;
    }
}

int main() {
    
}