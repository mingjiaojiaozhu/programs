#include <stdio.h>

typedef struct node {
    int value;
    struct node *next;
} ListNode;

typedef ListNode *pNode;

void selectionSort(pNode head) {
    pNode prev = head;
    while (prev->next) {
        pNode current = prev;
        for (pNode node = prev->next; node->next; node = node->next) {
            if (current->next->value > node->next->value) {
                current = node;
            }
        }

        if (prev != current) {
            pNode next = current->next;
            current->next = next->next;
            next->next = prev->next;
            prev->next = next;
        }
        prev = prev->next;
    }
}
