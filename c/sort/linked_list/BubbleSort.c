#include <stdio.h>

typedef struct node {
    int value;
    struct node *next;
} ListNode;

typedef ListNode *pNode;

void bubbleSort(pNode head) {
    pNode border = NULL;
    while (head->next->next != border) {
        int flag = 0;
        pNode prev = head;
        pNode current = head->next;
        while (current->next != border) {
            if (current->value > current->next->value) {
                pNode next = current->next;
                current->next = next->next;
                next->next = prev->next;
                prev->next = next;

                flag = 1;
                current = prev->next;
            }
            prev = prev->next;
            current = current->next;
        }
        border = current;

        if (!flag) {
            break;
        }
    }
}
