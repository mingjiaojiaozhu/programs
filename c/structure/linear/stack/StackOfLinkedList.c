#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node *next;
} ListNode;

typedef ListNode *pNode;

void create(pNode *head) {
    *head = (pNode) malloc(sizeof(ListNode));
    (*head)->value = 0;
    (*head)->next = NULL;
}

int isEmpty(pNode head) {
    return !head->next ? 1 : 0;
}

void push(pNode head, int value) {
    pNode node = (pNode) malloc(sizeof(ListNode));
    node->value = value;
    node->next = head->next;
    head->next = node;
}

int pop(pNode head) {
    if (head->next) {
        pNode node = head->next;
        head->next = node->next;
        return node->value;
    }
    return 1 << 31;
}

void clear(pNode head) {
    head->next = NULL;
}
