#include <iostream>
using namespace std;

struct ListNode {
    int value;
    ListNode *next;

    ListNode(int value) : value(value), next(nullptr) {}
};

class BubbleSort {
public:
    void sort(ListNode *head) {
        ListNode *border = nullptr;
        while (head->next->next != border) {
            bool flag = false;
            ListNode *prev = head;
            ListNode *current = head->next;
            while (current->next != border) {
                if (current->value > current->next->value) {
                    ListNode *next = current->next;
                    current->next = next->next;
                    next->next = prev->next;
                    prev->next = next;

                    flag = true;
                    current = prev->next;
                }
                prev = prev->next;
                current = current->next;
            }
            border = current;

            if (!flag) {
                break;
            }
        }
    }
};
