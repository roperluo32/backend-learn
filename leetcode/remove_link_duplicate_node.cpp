
#include <iostream>

using namespace std;

struct Node {
    Node* next;
    int value;
}

void removeDuplicate(Node *head) {
    Node* p = head->next;

    while (nullptr != p && nullptr != p->next) {
        if (p->value != p->next->value) {
            p = p->next;
            continue;
        }

        p->next = p->next->next;
    }
}


int main() {

}