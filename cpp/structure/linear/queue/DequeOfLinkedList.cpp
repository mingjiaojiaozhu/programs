#include <iostream>
using namespace std;

class DequeOfLinkedList {
public:
    DequeOfLinkedList() : head(new ListNode(0)), tail(new ListNode(0)) {
        head->next = tail;
        tail->prev = head;
    }

    bool isEmpty() {
        return head->next == tail;
    }

    void enqueueHead(int value) {
        ListNode *node = new ListNode(value);
        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;
    }

    void enqueueTail(int value) {
        ListNode *node = new ListNode(value);
        node->prev = tail->prev;
        node->next = tail;
        tail->prev->next = node;
        tail->prev = node;
    }

    int dequeueHead() {
        if (head->next != tail) {
            ListNode *node = head->next;
            node->next->prev = head;
            head->next = node->next;
            return node->value;
        }
        return INT_MIN;
    }

    int dequeueTail() {
        if (head->next != tail) {
            ListNode *node = tail->prev;
            node->prev->next = tail;
            tail->prev = node->prev;
            return node->value;
        }
        return INT_MIN;
    }

    void clear() {
        head->next = tail;
        tail->prev = head;
    }

private:
    struct ListNode {
        int value;
        ListNode *prev;
        ListNode *next;

        ListNode(int value) : value(value), prev(nullptr), next(nullptr) {}
    };

    ListNode *head;
    ListNode *tail;
};
