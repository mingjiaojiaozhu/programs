#include <iostream>
#include <unordered_map>
using namespace std;

class LRUCache {
public:
    LRUCache() : head(new HashNode(0, 0)), tail(new HashNode(0, 0)) {
        head->next = tail;
        tail->prev = head;
    }

    bool isEmpty() {
        return hash.empty();
    }

    void set(int key, int value) {
        if (hash.end() != hash.find(key)) {
            erase(hash[key]);
            hash[key] = new HashNode(key, value);
            add(hash[key]);
            return;
        }

        if ((int) hash.size() >= 64) {
            HashNode *node = head->next;
            erase(node);
            hash.erase(node->key);
        }

        HashNode *node = new HashNode(key, value);
        hash[key] = node;
        add(node);
    }

    int get(int key) {
        if (hash.end() != hash.find(key)) {
            HashNode *node = hash[key];
            erase(node);
            add(node);
            return node->value;
        }
        return INT_MIN;
    }

    void clear() {
        hash.clear();
        head->next = tail;
        tail->prev = head;
    }

private:
    struct HashNode {
        int key;
        int value;
        HashNode *prev;
        HashNode *next;

        HashNode(int key, int value): key(key), value(value), prev(nullptr), next(nullptr) {}
    };

    unordered_map<int, HashNode *> hash;
    HashNode *head;
    HashNode *tail;

    void add(HashNode *node) {
        HashNode *prev = tail->prev;
        node->prev = prev;
        node->next = tail;
        prev->next = node;
        tail->prev = node;
    }

    void erase(HashNode *node) {
        HashNode *prev = node->prev;
        HashNode *next = node->next;
        prev->next = next;
        next->prev = prev;
    }
};
