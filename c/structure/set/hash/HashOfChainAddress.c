#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int key;
    int value;
    struct node *next;
} HashNode;

typedef HashNode *pNode;

void create(pNode *hash) {
    *hash = (pNode) malloc(sizeof(HashNode) * 64);
    for (int i = 0; i < 64; ++i) {
        (*hash)[i].key = 0;
        (*hash)[i].value = 0;
        (*hash)[i].next = NULL;
    }
}

int isEmpty(pNode hash) {
    for (int i = 0; i < 64; ++i) {
        if (hash[i].next) {
            return 0;
        }
    }
    return 1;
}

void add(pNode hash, int key, int value) {
    pNode current = &hash[key % 64];
    while (current->next) {
        current = current->next;
        if (key == current->key) {
            current->value = value;
            return;
        }
    }
    pNode node = (pNode) malloc(sizeof(HashNode));
    node->key = key;
    node->value = value;
    current->next = node;
}

void erase(pNode hash, int key) {
    pNode current = &hash[key % 64];
    while (current->next) {
        if (key == current->next->key) {
            current->next = current->next->next;
            return;
        }
        current = current->next;
    }
}

void set(pNode hash, int key, int value) {
    pNode current = hash[key % 64].next;
    while (current && key != current->key) {
        current = current->next;
    }

    if (current) {
        current->value = value;
    }
}

int get(pNode hash, int key) {
    pNode current = hash[key % 64].next;
    while (current && key != current->key) {
        current = current->next;
    }

    if (current) {
        return current->value;
    }
    return 1 << 31;
}

void clear(pNode hash) {
    for (int i = 0; i < 64; ++i) {
        hash[i].next = NULL;
    }
}
