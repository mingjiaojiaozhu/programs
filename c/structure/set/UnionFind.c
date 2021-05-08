#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int *values;
    int *weights;
    int length;
} HashNode;

static int getRoot(HashNode hash, int value);

void create(HashNode *hash, int length) {
    hash->values = (int *) malloc(sizeof(int) * length);
    hash->weights = (int *) malloc(sizeof(int) * length);
    for (int i = 0; i < length; ++i) {
        hash->values[i] = -1;
        hash->weights[i] = 1;
    }
    hash->length = length;
}

void add(HashNode *hash, int start, int end) {
    if (start < 0 || start >= hash->length || end < 0 || end >= hash->length) {
        return;
    }

    int rootStart = getRoot(*hash, start);
    int rootEnd = getRoot(*hash, end);
    if (rootStart != rootEnd) {
        if (hash->weights[rootStart] < hash->weights[rootEnd]) {
            hash->values[rootEnd] = rootStart;
            hash->weights[rootStart] += hash->weights[rootEnd];
        } else {
            hash->values[rootStart] = rootEnd;
            hash->weights[rootEnd] += hash->weights[rootStart];
        }
    }
}

int contains(HashNode hash, int start, int end) {
    if (start >= 0 && start < hash.length && end >= 0 && end < hash.length) {
        return (getRoot(hash, start) == getRoot(hash, end)) ? 1 : 0;
    }
    return 0;
}

static int getRoot(HashNode hash, int value) {
    int root = value;
    while (~hash.values[root]) {
        root = hash.values[root];
    }

    while (value != root) {
        int aux = hash.values[value];
        hash.values[value] = root;
        value = aux;
    }
    return root;
}
