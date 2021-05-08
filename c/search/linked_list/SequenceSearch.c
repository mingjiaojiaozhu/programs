#include <stdio.h>

typedef struct node {
    int value;
    struct node *next;
} ListNode;

typedef ListNode *pNode;

pNode sequenceSearch(pNode head, int target) {
    pNode current = head->next;
    while (current) {
        if (target == current->value) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}
