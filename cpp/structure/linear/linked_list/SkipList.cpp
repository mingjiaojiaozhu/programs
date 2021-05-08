#include <iostream>
#include <ctime>
using namespace std;

class SkipList {
public:
    SkipList() : head(new ListNode(0)), maxLevel(1) {}

    bool isEmpty() {
        return !head->next[0];
    }

    void add(int value) {
        srand((unsigned int) time(nullptr));
        int num = rand() % 65536;
        int level = 0;
        while (num) {
            ++level;
            num &= num - 1;
        }

        ListNode **next = new ListNode *[level];
        for (int i = 0; i < level; ++i) {
            next[i] = head;
        }
        for (int i = level - 1; i >= 0; --i) {
            ListNode *current = head;
            while (current->next[i] && value > current->next[i]->value) {
                current = current->next[i];
            }

            if (current->next[i] && value == current->next[i]->value) {
                return;
            }
            next[i] = current;
        }

        ListNode *node = new ListNode(value);
        for (int i = 0; i < level; ++i) {
            node->next[i] = next[i]->next[i];
            next[i]->next[i] = node;
        }

        if (maxLevel < level) {
            maxLevel = level;
        }
    }

    void erase(int value) {
        ListNode **next = new ListNode *[maxLevel];
        ListNode *current = head;
        for (int i = maxLevel - 1; i >= 0; --i) {
            while (current->next[i] && value > current->next[i]->value) {
                current = current->next[i];
            }
            next[i] = current;
        }

        if (!current->next[0] || value != current->next[0]->value) {
            return;
        }

        for (int i = maxLevel - 1; i >= 0; --i) {
            if (next[i]->next[i] && value == next[i]->next[i]->value) {
                next[i]->next[i] = next[i]->next[i]->next[i];
            }
        }

        for (int i = maxLevel - 1; i >= 0; --i) {
            if (head->next[i]) {
                break;
            }
            --maxLevel;
        }
    }

    bool contains(int value) {
        ListNode *current = head;
        for (int i = maxLevel - 1; i >= 0; --i) {
            while (current->next[i] && value > current->next[i]->value) {
                current = current->next[i];
            }
        }
        return current->next[0] && value == current->next[0]->value;
    }

    void clear() {
        for (int i = 0; i < 16; ++i) {
            head->next[i] = nullptr;
        }
        maxLevel = 1;
    }

private:
    struct ListNode {
        int value;
        ListNode **next;

        ListNode(int value) : value(value) {
            next = new ListNode *[16];
            for (int i = 0; i < 16; ++i) {
                next[i] = nullptr;
            }
        }
    };

    ListNode *head;
    int maxLevel;
};
