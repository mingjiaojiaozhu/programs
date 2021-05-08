#include <iostream>
#include <vector>
using namespace std;

class HashOfChainAddress {
public:
    HashOfChainAddress() {
        for (int i = 0; i < 64; ++i) {
            hash.emplace_back(new HashNode(0, 0));
        }
    }

    bool isEmpty() {
        for (HashNode *node : hash) {
            if (node->next) {
                return false;
            }
        }
        return true;
    }

    void add(int key, int value) {
        HashNode *current = hash[key % 64];
        while (current->next) {
            current = current->next;
            if (key == current->key) {
                current->value = value;
                return;
            }
        }
        current->next = new HashNode(key, value);
    }

    void erase(int key) {
        HashNode *current = hash[key % 64];
        while (current->next) {
            if (key == current->next->key) {
                current->next = current->next->next;
                return;
            }
            current = current->next;
        }
    }

    void set(int key, int value) {
        HashNode *current = hash[key % 64]->next;
        while (current && key != current->key) {
            current = current->next;
        }

        if (current) {
            current->value = value;
        }
    }

    int get(int key) {
        HashNode *current = hash[key % 64]->next;
        while (current && key != current->key) {
            current = current->next;
        }

        if (current) {
            return current->value;
        }
        return INT_MIN;
    }

    void clear() {
        for (HashNode *node : hash) {
            node->next = nullptr;
        }
    }

private:
    struct HashNode {
        int key;
        int value;
        HashNode *next;

        HashNode(int key, int value): key(key), value(value), next(nullptr) {}
    };

    vector<HashNode *> hash;
};
