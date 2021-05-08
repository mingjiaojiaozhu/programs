#include <iostream>
using namespace std;

class StackOfLinkedList {
public:
    StackOfLinkedList() : head(new ListNode(0)) {}

    bool isEmpty() {
        return !head->next;
    }

    void push(int value) {
        ListNode *node = new ListNode(value);
        node->next = head->next;
        head->next = node;
    }

    int pop() {
        if (head->next) {
            ListNode *node = head->next;
            head->next = node->next;
            return node->value;
        }
        return INT_MIN;
    }

    void clear() {
        head->next = nullptr;
    }

private:
    struct ListNode {
        int value;
        ListNode *next;

        ListNode(int value) : value(value), next(nullptr) {}
    };

    ListNode *head;
};
