#include <iostream>
using namespace std;

struct ListNode {
    int value;
    ListNode *next;

    ListNode(int value) : value(value), next(nullptr) {}
};

class CircularLinkedList {
public:
    bool isCircular(ListNode *head) {
        ListNode *slow = head->next;
        ListNode *fast = head->next;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) {
                return true;
            }
        }
        return false;
    }

    int circularLength(ListNode *head) {
        ListNode *slow = head->next;
        ListNode *fast = head->next;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) {
                break;
            }
        }

        if (!fast || !fast->next) {
            return 0;
        }

        slow = slow->next;
        int count = 1;
        while (slow != fast) {
            slow = slow->next;
            ++count;
        }
        return count;
    }

    ListNode *circularEntry(ListNode *head) {
        ListNode *slow = head->next;
        ListNode *fast = head->next;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) {
                break;
            }
        }

        if (!fast || !fast->next) {
            return nullptr;
        }

        fast = head->next;
        while (slow != fast) {
            slow = slow->next;
            fast = fast->next;
        }
        return slow;
    }
};
