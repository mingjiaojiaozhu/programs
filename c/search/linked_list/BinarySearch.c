#include <stdio.h>

typedef struct node {
    int value;
    struct node *next;
} ListNode;

typedef ListNode *pNode;

static pNode search(pNode start, pNode end, int target);
static pNode getMiddle(pNode start, pNode end);

pNode binarySearch(pNode head, int target) {
    return search(head->next, NULL, target);
}

static pNode search(pNode start, pNode end, int target) {
    if (start == end) {
        return (start && target == start->value) ? start : NULL;
    }

    pNode middle = getMiddle(start, end);
    if (target == middle->value) {
        return middle;
    }

    if (target < middle->value) {
        return search(start, middle, target);
    }
    return search(middle->next, NULL, target);
}

static pNode getMiddle(pNode start, pNode end) {
    pNode slow = start;
    pNode fast = start->next;
    while (fast != end && fast->next != end) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}
