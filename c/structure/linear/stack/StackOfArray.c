#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *values;
    int length;
    int capacity;
} ArrayNode;

void create(ArrayNode *arrays) {
    arrays->values = (int *) malloc(sizeof(int) * 64);
    memset(arrays->values, 0, sizeof(int) * 64);
    arrays->length = 0;
    arrays->capacity = 64;
}

int isEmpty(ArrayNode arrays) {
    return !arrays.length ? 1 : 0;
}

void push(ArrayNode *arrays, int value) {
    if (arrays->length >= arrays->capacity) {
        arrays->values = (int *) realloc(arrays->values, sizeof(int) * (arrays->capacity + 16));
        memset(arrays->values + arrays->capacity, 0, sizeof(int) * 16);
        arrays->capacity += 16;
    }

    arrays->values[arrays->length] = value;
    ++arrays->length;
}

int pop(ArrayNode *arrays) {
    if (arrays->length) {
        --arrays->length;
        return arrays->values[arrays->length];
    }
    return 1 << 31;
}

void clear(ArrayNode *arrays) {
    memset(arrays->values, 0, sizeof(int) * arrays->capacity);
    arrays->length = 0;
}
