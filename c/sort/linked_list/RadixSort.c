#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node *next;
} ListNode;

typedef ListNode *pNode;

void radixSort(pNode head) {
    int maxValue = head->next->value;
    int minValue = head->next->value;
    pNode current = head->next->next;
    while (current) {
        if (maxValue < current->value) {
            maxValue = current->value;
        }
        if (minValue > current->value) {
            minValue = current->value;
        }
        current = current->next;
    }

    pNode *buckets = (pNode *) malloc(sizeof(pNode) * 10);
    for (int i = 0; i < 10; ++i) {
        buckets[i] = (pNode) malloc(sizeof(ListNode));
    }

    int diff = maxValue - minValue;
    for (int gap = 1; gap <= diff; gap *= 10) {
        for (int i = 0; i < 10; ++i) {
            buckets[i]->next = NULL;
        }

        current = head->next;
        while (current) {
            pNode bucket = buckets[((current->value - minValue) / gap) % 10];
            while (bucket->next) {
                bucket = bucket->next;
            }
            bucket->next = current;
            current = current->next;
            bucket->next->next = NULL;
        }

        current = head;
        for (int i = 0; i < 10; ++i) {
            current->next = buckets[i]->next;
            while (current->next) {
                current = current->next;
            }
        }
        current->next = NULL;
    }
}
