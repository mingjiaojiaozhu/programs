#include <stdio.h>

typedef struct node {
    int value;
    struct node *next;
} ListNode;

typedef ListNode *pNode;

int isCircular(pNode head) {
    pNode slow = head->next;
    pNode fast = head->next;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            return 1;
        }
    }
    return 0;
}

int circularLength(pNode head) {
    pNode slow = head->next;
    pNode fast = head->next;
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

pNode circularEntry(pNode head) {
    pNode slow = head->next;
    pNode fast = head->next;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            break;
        }
    }

    if (!fast || !fast->next) {
        return NULL;
    }

    fast = head->next;
    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }
    return slow;
}
