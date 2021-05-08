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

void enqueue(ArrayNode *arrays, int value) {
    if (arrays->length >= arrays->capacity) {
        arrays->values = (int *) realloc(arrays->values, sizeof(int) * (arrays->capacity + 16));
        memset(arrays->values + arrays->capacity, 0, sizeof(int) * 16);
        arrays->capacity += 16;
    }

    int child = arrays->length;
    while (child > 0) {
        int parent = (child - 1) >> 1;
        if (arrays->values[parent] <= value) {
            break;
        }
        arrays->values[child] = arrays->values[parent];
        child = parent;
    }
    arrays->values[child] = value;
    ++arrays->length;
}

int dequeue(ArrayNode *arrays) {
    if (!arrays->length) {
        return 1 << 31;
    }

    --arrays->length;
    int value = arrays->values[0];
    int pivot = arrays->values[arrays->length];
    int parent = 0;
    while (1) {
        int child = (parent << 1) + 1;
        if (child >= arrays->length) {
            break;
        }

        if (child < arrays->length - 1 && arrays->values[child] > arrays->values[child + 1]) {
            ++child;
        }
        if (arrays->values[child] >= pivot) {
            break;
        }
        arrays->values[parent] = arrays->values[child];
        parent = child;
    }
    arrays->values[parent] = pivot;
    return value;
}

void clear(ArrayNode *arrays) {
    memset(arrays->values, 0, sizeof(int) * arrays->capacity);
    arrays->length = 0;
}
