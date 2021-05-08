#include <iostream>
#include <vector>
using namespace std;

class HashOfOpenAddress {
public:
    HashOfOpenAddress() {
        for (int i = 0; i < 256; ++i) {
            hash.emplace_back(new HashNode(0, 0));
        }
    }

    bool isEmpty() {
        for (HashNode *node : hash) {
            if (node->used) {
                return false;
            }
        }
        return true;
    }

    void add(int key, int value) {
        int index = key % 256;
        for (int i = 0; i < 256; ++i) {
            HashNode *current = hash[index];
            if (current->used && key == current->key) {
                current->value = value;
                return;
            }

            if (!current->used) {
                current->key = key;
                current->value = value;
                current->used = true;
                return;
            }

            ++index;
            if (index >= 256) {
                index = 0;
            }
        }
    }

    void erase(int key) {
        int index = key % 256;
        for (int i = 0; i < 256; ++i) {
            HashNode *current = hash[index];
            if (current->used && key == current->key) {
                current->key = 0;
                current->value = 0;
                current->used = false;
                return;
            }

            ++index;
            if (index >= 256) {
                index = 0;
            }
        }
    }

    void set(int key, int value) {
        int index = key % 256;
        for (int i = 0; i < 256; ++i) {
            HashNode *current = hash[index];
            if (current->used && key == current->key) {
                current->value = value;
                return;
            }

            ++index;
            if (index >= 256) {
                index = 0;
            }
        }
    }

    int get(int key) {
        int index = key % 256;
        for (int i = 0; i < 256; ++i) {
            HashNode *current = hash[index];
            if (current->used && key == current->key) {
                return current->value;
            }

            ++index;
            if (index >= 256) {
                index = 0;
            }
        }
        return INT_MIN;
    }

    void clear() {
        for (HashNode *node : hash) {
            node->key = 0;
            node->value = 0;
            node->used = false;
        }
    }

private:
    struct HashNode {
        int key;
        int value;
        bool used;

        HashNode(int key, int value): key(key), value(value), used(false) {}
    };

    vector<HashNode *> hash;
};
