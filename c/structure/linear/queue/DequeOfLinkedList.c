#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node *prev;
    struct node *next;
} ListNode;

typedef struct {
    ListNode *head;
    ListNode *tail;
} DoublyListNode;

void create(DoublyListNode *list) {
    list->head = (ListNode *) malloc(sizeof(ListNode));
    list->tail = (ListNode *) malloc(sizeof(ListNode));
    list->head->value = 0;
    list->tail->value = 0;
    list->head->prev = NULL;
    list->tail->prev = list->head;
    list->head->next = list->tail;
    list->tail->next = NULL;
}

int isEmpty(DoublyListNode list) {
    return (list.head->next == list.tail) ? 1 : 0;
}

void enqueueHead(DoublyListNode *list, int value) {
    ListNode *node = (ListNode *) malloc(sizeof(ListNode));
    node->value = value;
    node->next = list->head->next;
    node->prev = list->head;
    list->head->next->prev = node;
    list->head->next = node;
}

void enqueueTail(DoublyListNode *list, int value) {
    ListNode *node = (ListNode *) malloc(sizeof(ListNode));
    node->value = value;
    node->prev = list->tail->prev;
    node->next = list->tail;
    list->tail->prev->next = node;
    list->tail->prev = node;
}

int dequeueHead(DoublyListNode *list) {
    if (list->head->next != list->tail) {
        ListNode *node = list->head->next;
        node->next->prev = list->head;
        list->head->next = node->next;
        return node->value;
    }
    return 1 << 31;
}

int dequeueTail(DoublyListNode *list) {
    if (list->head->next != list->tail) {
        ListNode *node = list->tail->prev;
        node->prev->next = list->tail;
        list->tail->prev = node->prev;
        return node->value;
    }
    return 1 << 31;
}

void clear(DoublyListNode *list) {
    list->head->next = list->tail;
    list->tail->prev = list->head;
}
