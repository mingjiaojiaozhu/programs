#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node *next;
} ListNode;

typedef ListNode *pNode;

static void sort(pNode head, pNode start, pNode end);
static pNode getPartition(pNode head, pNode start, pNode end);

void quickSort(pNode head) {
    sort(head, head->next, NULL);
}

static void sort(pNode head, pNode start, pNode end) {
    if (start != end && start->next != end) {
        pNode partition = getPartition(head, start, end);
        sort(head, head->next, partition);
        sort(partition, partition->next, end);
    }
}

static pNode getPartition(pNode head, pNode start, pNode end) {
    pNode headLeft = (pNode) malloc(sizeof(ListNode));
    pNode headRight = (pNode) malloc(sizeof(ListNode));
    headLeft->value = 0;
    headRight->value = 0;
    headLeft->next = NULL;
    headRight->next = NULL;

    pNode left = headLeft;
    pNode right = headRight;
    int pivot = start->value;
    for (pNode node = start->next; node != end; node = node->next) {
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
