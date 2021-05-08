#include <iostream>
using namespace std;

class QueueOfLinkedList {
public:
    QueueOfLinkedList() : head(new ListNode(0)), tail(new ListNode(0)) {
        head->next = tail;
        tail->prev = head;
    }

    bool isEmpty() {
        return head->next == tail;
    }

    void enqueue(int value) {
        ListNode *node = new ListNode(value);
        node->prev = tail->prev;
        node->next = tail;
        tail->prev->next = node;
        tail->prev = node;
    }

    int dequeue() {
        if (head->next != tail) {
            ListNode *node = head->next;
            node->next->prev = head;
            head->next = node->next;
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
