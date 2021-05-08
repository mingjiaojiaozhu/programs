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

void add(pNode head, int index, int value) {
    pNode current = head;
    int count = 0;
    while (current && count < index) {
        current = current->next;
        ++count;
    }

    if (current && count <= index) {
        pNode node = (pNode) malloc(sizeof(ListNode));
        node->value = value;
        node->next = current->next;
        current->next = node;
    }
}

void addHead(pNode head, int value) {
    pNode node = (pNode) malloc(sizeof(ListNode));
    node->value = value;
    node->next = head->next;
    head->next = node;
}

void addTail(pNode head, int value) {
    pNode current = head;
    while (current->next) {
        current = current->next;
    }

    pNode node = (pNode) malloc(sizeof(ListNode));
    node->value = value;
    node->next = NULL;
    current->next = node;
}

void erase(pNode head, int index) {
    pNode current = head;
    int count = 0;
    while (current->next && count < index) {
        current = current->next;
        ++count;
    }

    if (current->next && count <= index) {
        current->next = current->next->next;
    }
}

void eraseHead(pNode head) {
    if (head->next) {
        head->next = head->next->next;
    }
}

void eraseTail(pNode head) {
    if (!head->next) {
        return;
    }

    pNode current = head;
    while (current->next->next) {
        current = current->next;
    }
    current->next = NULL;
}

void set(pNode head, int index, int value) {
    pNode current = head->next;
    int count = 0;
    while (current && count < index) {
        current = current->next;
        ++count;
    }

    if (current && count <= index) {
        current->value = value;
    }
}

int get(pNode head, int index) {
    pNode current = head->next;
    int count = 0;
    while (current && count < index) {
        current = current->next;
        ++count;
    }

    if (current && count <= index) {
        return current->value;
    }
    return 1 << 31;
}

void reverse(pNode head) {
    pNode prev = NULL;
    pNode current = head->next;
    while (current) {
        pNode next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    head->next = prev;
}

void clear(pNode head) {
    head->next = NULL;
}
