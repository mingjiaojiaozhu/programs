#include <iostream>
using namespace std;

class SinglyLinkedList {
public:
    SinglyLinkedList() : head(new ListNode(0)) {}

    bool isEmpty() {
        return !head->next;
    }

    void add(int index, int value) {
        ListNode *current = head;
        int count = 0;
        while (current && count < index) {
            current = current->next;
            ++count;
        }

        if (current && count <= index) {
            ListNode *node = new ListNode(value);
            node->next = current->next;
            current->next = node;
        }
    }

    void addHead(int value) {
        ListNode *node = new ListNode(value);
        node->next = head->next;
        head->next = node;
    }

    void addTail(int value) {
        ListNode *current = head;
        while (current->next) {
            current = current->next;
        }

        ListNode *node = new ListNode(value);
        node->next = nullptr;
        current->next = node;
    }

    void erase(int index) {
        ListNode *current = head;
        int count = 0;
        while (current->next && count < index) {
            current = current->next;
            ++count;
        }

        if (current->next && count <= index) {
            current->next = current->next->next;
        }
    }

    void eraseHead() {
        if (head->next) {
            head->next = head->next->next;
        }
    }

    void eraseTail() {
        if (!head->next) {
            return;
        }

        ListNode *current = head;
        while (current->next->next) {
            current = current->next;
        }
        current->next = nullptr;
    }

    void set(int index, int value) {
        ListNode *current = head->next;
        int count = 0;
        while (current && count < index) {
            current = current->next;
            ++count;
        }

        if (current && count <= index) {
            current->value = value;
        }
    }

    int get(int index) {
        ListNode *current = head->next;
        int count = 0;
        while (current && count < index) {
            current = current->next;
            ++count;
        }

        if (current && count <= index) {
            return current->value;
        }
        return INT_MIN;
    }

    void reverse() {
        ListNode *prev = nullptr;
        ListNode *current = head->next;
        while (current) {
            ListNode *next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        head->next = prev;
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
