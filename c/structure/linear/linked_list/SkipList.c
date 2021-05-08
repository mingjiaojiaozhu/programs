#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node {
    int value;
    struct node **next;
} ListNode;

typedef struct {
    ListNode *head;
    int maxLevel;
} SkipListNode;

void create(SkipListNode *skip) {
    skip->head = (ListNode *) malloc(sizeof(ListNode));
    skip->head->value = 0;
    skip->head->next = (ListNode **) malloc(sizeof(ListNode *) * 16);
    for (int i = 0; i < 16; ++i) {
        skip->head->next[i] = NULL;
    }
    skip->maxLevel = 1;
}

int isEmpty(SkipListNode skip) {
    return !skip.head->next[0] ? 1 : 0;
}

void add(SkipListNode *skip, int value) {
    srand((unsigned int) time(NULL));
    int num = rand() % 65536;
    int level = 0;
    while (num) {
        ++level;
        num &= num - 1;
    }

    ListNode **next = (ListNode **) malloc(sizeof(ListNode *) * level);
    for (int i = 0; i < level; ++i) {
        next[i] = skip->head;
    }
    for (int i = level - 1; i >= 0; --i) {
        ListNode *current = skip->head;
        while (current->next[i] && value > current->next[i]->value) {
            current = current->next[i];
        }

        if (current->next[i] && value == current->next[i]->value) {
            return;
        }
        next[i] = current;
    }

    ListNode *node = (ListNode *) malloc(sizeof(ListNode));
    node->value = value;
    node->next = (ListNode **) malloc(sizeof(ListNode *) * 16);
    for (int i = 0; i < level; ++i) {
        node->next[i] = next[i]->next[i];
        next[i]->next[i] = node;
    }
    for (int i = level; i < 16; ++i) {
        node->next[i] = NULL;
    }

    if (skip->maxLevel < level) {
        skip->maxLevel = level;
    }
}

void erase(SkipListNode *skip, int value) {
    ListNode **next = (ListNode **) malloc(sizeof(ListNode *) * skip->maxLevel);
    ListNode *current = skip->head;
    for (int i = skip->maxLevel - 1; i >= 0; --i) {
        while (current->next[i] && value > current->next[i]->value) {
            current = current->next[i];
        }
        next[i] = current;
    }

    if (!current->next[0] || value != current->next[0]->value) {
        return;
    }

    for (int i = skip->maxLevel - 1; i >= 0; --i) {
        if (next[i]->next[i] && value == next[i]->next[i]->value) {
            next[i]->next[i] = next[i]->next[i]->next[i];
        }
    }

    for (int i = skip->maxLevel - 1; i >= 0; --i) {
        if (skip->head->next[i]) {
            break;
        }
        --skip->maxLevel;
    }
}

int contains(SkipListNode skip, int value) {
    ListNode *current = skip.head;
    for (int i = skip.maxLevel - 1; i >= 0; --i) {
        while (current->next[i] && value > current->next[i]->value) {
            current = current->next[i];
        }
    }
    return (current->next[0] && value == current->next[0]->value) ? 1 : 0;
}

void clear(SkipListNode *skip) {
    for (int i = 0; i < 16; ++i) {
        skip->head->next[i] = NULL;
    }
    skip->maxLevel = 1;
}
