#include <iostream>
using namespace std;

struct ListNode {
    int value;
    ListNode *next;

    ListNode(int value) : value(value), next(nullptr) {}
};

class SelectionSort {
public:
    void sort(ListNode *head) {
        ListNode *prev = head;
        while (prev->next) {
            ListNode *current = prev;
            for (ListNode *node = prev->next; node->next; node = node->next) {
                if (current->next->value > node->next->value) {
                    current = node;
                }
            }

            if (prev != current) {
                ListNode *next = current->next;
                current->next = next->next;
                next->next = prev->next;
                prev->next = next;
            }
            prev = prev->next;
        }
    }
};
