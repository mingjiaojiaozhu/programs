#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
    int value;
    int used;
} HashNode;

typedef HashNode *pNode;

void create(pNode *hash) {
    *hash = (pNode) malloc(sizeof(HashNode) * 256);
    for (int i = 0; i < 256; ++i) {
        (*hash)[i].key = 0;
        (*hash)[i].value = 0;
        (*hash)[i].used = 0;
    }
}

int isEmpty(pNode hash) {
    for (int i = 0; i < 256; ++i) {
        if (hash[i].used) {
            return 0;
        }
    }
    return 1;
}

void add(pNode hash, int key, int value) {
    int index = key % 256;
    for (int i = 0; i < 256; ++i) {
        pNode current = &hash[index];
        if (current->used && key == current->key) {
            current->value = value;
            return;
        }

        if (!current->used) {
            current->key = key;
            current->value = value;
            current->used = 1;
            return;
        }

        ++index;
        if (index >= 256) {
            index = 0;
        }
    }
}

void erase(pNode hash, int key) {
    int index = key % 256;
    for (int i = 0; i < 256; ++i) {
        pNode current = &hash[index];
        if (current->used && key == current->key) {
            current->key = 0;
            current->value = 0;
            current->used = 0;
            return;
        }

        ++index;
        if (index >= 256) {
            index = 0;
        }
    }
}

void set(pNode hash, int key, int value) {
    int index = key % 256;
    for (int i = 0; i < 256; ++i) {
        pNode current = &hash[index];
        if (current->used && key == current->key) {
            current->value = value;
            return;
        }

        ++index;
        if (index >= 256) {
            index = 0;
        }
    }
}

int get(pNode hash, int key) {
    int index = key % 256;
    for (int i = 0; i < 256; ++i) {
        pNode current = &hash[index];
        if (current->used && key == current->key) {
            return current->value;
        }

        ++index;
        if (index >= 256) {
            index = 0;
        }
    }
    return 1 << 31;
}

void clear(pNode hash) {
    for (int i = 0; i < 256; ++i) {
        hash[i].key = 0;
        hash[i].value = 0;
        hash[i].used = 0;
    }
}
