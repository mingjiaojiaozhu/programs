#include <iostream>
using namespace std;

struct ListNode {
    int value;
    ListNode *next;

    ListNode(int value) : value(value), next(nullptr) {}
};

class QuickSort {
public:
    void sort(ListNode *head) {
        sort(head, head->next, nullptr);
    }

private:
    void sort(ListNode *head, ListNode *start, ListNode *end) {
        if (start != end && start->next != end) {
            ListNode *partition = getPartition(head, start, end);
            sort(head, head->next, partition);
            sort(partition, partition->next, end);
        }
    }

    ListNode *getPartition(ListNode *head, ListNode *start, ListNode *end) {
        ListNode *headLeft = new ListNode(0);
        ListNode *headRight = new ListNode(0);

        ListNode *left = headLeft;
        ListNode *right = headRight;
        int pivot = start->value;
        for (ListNode *node = start->next; node != end; node = node->next) {
            if (node->value < pivot) {
                left->next = node;
                left = node;
            } else {
                right->next = node;
                right = node;
            }
        }
        left->next = start;
        right->next = end;

        head->next = headLeft->next;
        start->next = headRight->next;
        return start;
    }
};
