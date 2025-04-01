
#include <unordered_map>
#include <iostream>

using namespace std;

struct DLinkNode {
    DLinkNode* pre;
    DLinkNode* next;
    int key, value;
    DLinkNode(): pre(nullptr), next(nullptr) {};
    DLinkNode(int _key, int _value): key(_key), value(_value), pre(nullptr), next(nullptr) {};
};

struct LRU {
    int cap;
    int size;
    unordered_map<int, DLinkNode*> cache;
    DLinkNode* head;
    DLinkNode* tail;

    LRU(int _cap): cap(_cap) {
        head = new DLinkNode();
        tail = new DLinkNode();
        head->next = head->pre = tail;
        tail->next = tail->pre = head;
    }

    void deleteNode(DLinkNode* node) {
        node->pre->next = node->next;
        node->next->pre = node->pre;
    }

    void addToHead(DLinkNode* node) {
        node->next = head->next;
        node->pre = head;
        head->next->pre = node;
        head->next = node;
    }

    void deleteTail() {
        if (cache.size() == 0) { return; }
        DLinkNode* node = tail->pre;
        cache.erase(node->key);
        deleteNode(node);
        delete node;
    }

    int get(int key) {
        if (cache.count(key) == 0) { return -1;}

        DLinkNode* node = cache[key];
        deleteNode(node);
        addToHead(node);

        return node->value;
    }

    void put(int key, int value) {
        if (cache.count(key) > 0) {
            DLinkNode* node = cache[key];
            node->value = value;

            deleteNode(node);
            addToHead(node);
        } else {
            DLinkNode* newNode = new DLinkNode(key, value);
            cache[key] = newNode;
            addToHead(newNode);
            size++;
            cout << "size: " << cache.size() << " cap:" << cap << endl;
            if (cache.size() > cap) {
                deleteTail();
                size--;
            }
        }
    }
};


int main() {
    cout << "hello" << endl;

    LRU lru = LRU(2);
    lru.put(1, 10);
    cout << lru.get(1) << endl;
    lru.put(2, 20);
    lru.put(3, 30);
    cout << lru.get(1) << endl;
}