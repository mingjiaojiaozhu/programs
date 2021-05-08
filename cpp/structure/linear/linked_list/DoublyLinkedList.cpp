#include <iostream>
using namespace std;

class DoublyLinkedList {
public:
    DoublyLinkedList() : head(new ListNode(0)), tail(new ListNode(0)) {
        head->next = tail;
        tail->prev = head;
    }

    bool isEmpty() {
        return head->next == tail;
    }

    void add(int index, int value) {
        ListNode *current = head;
        int count = 0;
        while (current != tail && count < index) {
            current = current->next;
            ++count;
        }

        if (current != tail && count <= index) {
            ListNode *node = new ListNode(value);
            node->next = current->next;
            node->prev = current;
            current->next->prev = node;
            current->next = node;
        }
    }

    void addHead(int value) {
        ListNode *node = new ListNode(value);
        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;
    }

    void addTail(int value) {
        ListNode *node = new ListNode(value);
        node->prev = tail->prev;
        node->next = tail;
        tail->prev->next = node;
        tail->prev = node;
    }

    void erase(int index) {
        ListNode *current = head;
        int count = 0;
        while (current->next != tail && count < index) {
            current = current->next;
            ++count;
        }

        if (current->next == tail || count > index) {
            return;
        }
        current->next->next->prev = current;
        current->next = current->next->next;
    }

    void eraseHead() {
        if (head->next != tail) {
            head->next->next->prev = head;
            head->next = head->next->next;
        }
    }

    void eraseTail() {
        if (head->next != tail) {
            tail->prev->prev->next = tail;
            tail->prev = tail->prev->prev;
        }
    }

    void set(int index, int value) {
        ListNode *current = head->next;
        int count = 0;
        while (current != tail && count < index) {
            current = current->next;
            ++count;
        }

        if (current != tail && count <= index) {
            current->value = value;
        }
    }

    int get(int index) {
        ListNode *current = head->next;
        int count = 0;
        while (current != tail && count < index) {
            current = current->next;
            ++count;
        }

        if (current != tail && count <= index) {
            return current->value;
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
