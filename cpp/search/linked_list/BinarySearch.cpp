#include <iostream>
using namespace std;

struct ListNode {
    int value;
    ListNode *next;

    ListNode(int value) : value(value), next(nullptr) {}
};

class BinarySearch {
public:
    ListNode *search(ListNode *head, int target) {
        return search(head->next, nullptr, target);
    }

private:
    ListNode *search(ListNode *start, ListNode *end, int target) {
        if (start == end) {
            return (start && target == start->value) ? start : nullptr;
        }

        ListNode *middle = getMiddle(start, end);
        if (target == middle->value) {
            return middle;
        }

        if (target < middle->value) {
            return search(start, middle, target);
        }
        return search(middle->next, nullptr, target);
    }

    ListNode *getMiddle(ListNode *start, ListNode *end) {
        ListNode *slow = start;
        ListNode *fast = start->next;
        while (fast != end && fast->next != end) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }
};
