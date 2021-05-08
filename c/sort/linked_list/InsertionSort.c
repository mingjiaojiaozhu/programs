#include <stdio.h>

typedef struct node {
    int value;
    struct node *next;
} ListNode;

typedef ListNode *pNode;

void insertionSort(pNode head) {
    pNode current = head->next;
    while (current->next) {
        pNode prev = head;
        while (prev != current && prev->next->value <= current->next->value) {
            prev = prev->next;
        }

        if (prev == current) {
            current = current->next;
        } else {
            pNode next = current->next;
            current->next = next->next;
            next->next = prev->next;
            prev->next = next;
        }
    }
}
