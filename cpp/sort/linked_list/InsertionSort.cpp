#include <iostream>
using namespace std;

struct ListNode {
    int value;
    ListNode *next;

    ListNode(int value) : value(value), next(nullptr) {}
};

class InsertionSort {
public:
    void sort(ListNode *head) {
        ListNode *current = head->next;
        while (current->next) {
            ListNode *prev = head;
            while (prev != current && prev->next->value <= current->next->value) {
                prev = prev->next;
            }

            if (prev == current) {
                current = current->next;
            } else {
                ListNode *next = current->next;
                current->next = next->next;
                next->next = prev->next;
                prev->next = next;
            }
        }
    }
};
