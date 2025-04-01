#include <iostream>
#include <unordered_map>

using namespace std;

struct DLinkNode {
    DLinkNode* prev;
    DLinkNode* next;
    int key;
    int value;

    DLinkNode(): prev(nullptr), next(nullptr) {}
    DLinkNode(int _key, int _value): key(_key), value(_value), prev(nullptr), next(nullptr) {}
};


struct LRU {
    unordered_map<int, DLinkNode*> cache;
    int cap;
    int size;
    DLinkNode* head;
    DLinkNode* tail;

    LRU(int _cap): cap(_cap), size(0) {
        head = new DLinkNode();
        tail = new DLinkNode();
        head->prev = tail;
        head->next = tail;
        tail->prev = head;
        tail->next = head;
    }

    void addToHead(DLinkNode* node) {
        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;
    }

    void removeNode(DLinkNode* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    DLinkNode* deleteTail() {
        DLinkNode* node = tail->prev;
        removeNode(node);
        return node;
    }

    int get(int key) {
        if (cache.count(key) == 0) { return -1; }
        DLinkNode* node = cache[key];
        removeNode(node);
        addToHead(node);

        return node->value;
    }

    void put(int key, int value) {
        if (cache.count(key) > 0) {
            DLinkNode* node = cache[key];
            node->value = value;
            removeNode(node);
            addToHead(node);
        } else {
            DLinkNode* newNode = new DLinkNode(key, value);
            cache[key] = newNode;
            addToHead(newNode);
            size++;

            if (size > cap) {
                DLinkNode* lastNode = deleteTail();
                cache.erase(lastNode->key);
                delete lastNode;
                size--;
            }
        }
    }
};


int main() {
    LRU lru = LRU(2);
    lru.put(2, 20);
    cout << lru.get(2) << endl;

    lru.put(3, 30);
    lru.put(5, 50);

    cout << lru.get(2) << endl;
    cout << lru.get(5) << endl;
}