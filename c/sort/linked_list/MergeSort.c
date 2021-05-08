#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node *next;
} ListNode;

typedef ListNode *pNode;

static void sort(pNode head, pNode start);
static void merge(pNode head, pNode left, pNode right);
static pNode getMiddle(pNode start);

void mergeSort(pNode head) {
    sort(head, head->next);
}

static void sort(pNode head, pNode start) {
    if (!start->next) {
        head->next = start;
        return;
    }

    pNode left = (pNode) malloc(sizeof(ListNode));
    pNode right = (pNode) malloc(sizeof(ListNode));
    left->value = 0;
    right->value = 0;
    pNode middle = getMiddle(start);
    left->next = start;
    right->next = middle->next;
    middle->next = NULL;

    sort(left, left->next);
    sort(right, right->next);
    merge(head, left->next, right->next);
}

static void merge(pNode head, pNode left, pNode right) {
    pNode current = head;
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

static pNode getMiddle(pNode start) {
    if (!start->next) {
        return start;
    }

    pNode slow = start;
    pNode fast = start->next;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}
