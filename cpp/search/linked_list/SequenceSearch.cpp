#include <iostream>
using namespace std;

struct ListNode {
    int value;
    ListNode *next;

    ListNode(int value) : value(value), next(nullptr) {}
};

class SequenceSearch {
public:
    ListNode *search(ListNode *head, int target) {
        ListNode *current = head->next;
        while (current) {
            if (target == current->value) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }
};
