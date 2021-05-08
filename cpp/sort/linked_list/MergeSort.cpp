#include <iostream>
using namespace std;

struct ListNode {
    int value;
    ListNode *next;

    ListNode(int value) : value(value), next(nullptr) {}
};

class MergeSort {
public:
    void sort(ListNode *head) {
        sort(head, head->next);
    }

private:
    void sort(ListNode *head, ListNode *start) {
        if (!start->next) {
            head->next = start;
            return;
        }

        ListNode *left = new ListNode(0);
        ListNode *right = new ListNode(0);
        ListNode *middle = getMiddle(start);
        left->next = start;
        right->next = middle->next;
        middle->next = nullptr;

        sort(left, left->next);
        sort(right, right->next);
        merge(head, left->next, right->next);
    }

    void merge(ListNode *head, ListNode *left, ListNode *right) {
        ListNode *current = head;
        while (left && right) {
            if (left->value > right->value) {
                current->next = right;
                right = right->next;
            } else {
                current->next = left;
                left = left->next;
            }
            current = current->next;
        }

        if (left) {
            current->next = left;
        }
        if (right) {
            current->next = right;
        }
    }

    ListNode *getMiddle(ListNode *start) {
        if (!start->next) {
            return start;
        }

        ListNode *slow = start;
        ListNode *fast = start->next;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }
};
