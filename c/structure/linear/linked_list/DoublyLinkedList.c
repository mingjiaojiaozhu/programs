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

void add(DoublyListNode *list, int index, int value) {
    ListNode *current = list->head;
    int count = 0;
    while (current != list->tail && count < index) {
        current = current->next;
        ++count;
    }

    if (current != list->tail && count <= index) {
        ListNode *node = (ListNode *) malloc(sizeof(ListNode));
        node->value = value;
        node->next = current->next;
        node->prev = current;
        current->next->prev = node;
        current->next = node;
    }
}

void addHead(DoublyListNode *list, int value) {
    ListNode *node = (ListNode *) malloc(sizeof(ListNode));
    node->value = value;
    node->next = list->head->next;
    node->prev = list->head;
    list->head->next->prev = node;
    list->head->next = node;
}

void addTail(DoublyListNode *list, int value) {
    ListNode *node = (ListNode *) malloc(sizeof(ListNode));
    node->value = value;
    node->prev = list->tail->prev;
    node->next = list->tail;
    list->tail->prev->next = node;
    list->tail->prev = node;
}

void erase(DoublyListNode *list, int index) {
    ListNode *current = list->head;
    int count = 0;
    while (current->next != list->tail && count < index) {
        current = current->next;
        ++count;
    }

    if (current->next != list->tail && count <= index) {
        current->next->next->prev = current;
        current->next = current->next->next;
    }
}

void eraseHead(DoublyListNode *list) {
    if (list->head->next != list->tail) {
        list->head->next->next->prev = list->head;
        list->head->next = list->head->next->next;
    }
}

void eraseTail(DoublyListNode *list) {
    if (list->head->next != list->tail) {
        list->tail->prev->prev->next = list->tail;
        list->tail->prev = list->tail->prev->prev;
    }
}

void set(DoublyListNode *list, int index, int value) {
    ListNode *current = list->head->next;
    int count = 0;
    while (current && count < index) {
        current = current->next;
        ++count;
    }

    if (current != list->tail && count <= index) {
        current->value = value;
    }
}

int get(DoublyListNode list, int index) {
    ListNode *current = list.head->next;
    int count = 0;
    while (current && count < index) {
        current = current->next;
        ++count;
    }

    if (current != list.tail && count <= index) {
        return current->value;
    }
    return 1 << 31;
}

void clear(DoublyListNode *list) {
    list->head->next = list->tail;
    list->tail->prev = list->head;
}
