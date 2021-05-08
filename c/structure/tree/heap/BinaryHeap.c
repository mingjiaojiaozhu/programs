#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *values;
    int length;
    int capacity;
} ArrayNode;

static void adjustHeapUp(ArrayNode *arrays, int child, int value);
static void adjustHeapDown(ArrayNode *arrays, int parent, int value);

void create(ArrayNode *arrays) {
    arrays->values = (int *) malloc(sizeof(int) * 64);
    memset(arrays->values, 0, sizeof(int) * 64);
    arrays->length = 0;
    arrays->capacity = 64;
}

int isEmpty(ArrayNode arrays) {
    return !arrays.length ? 1 : 0;
}

void add(ArrayNode *arrays, int value) {
    if (arrays->length >= arrays->capacity) {
        arrays->values = (int *) realloc(arrays->values, sizeof(int) * (arrays->capacity + 16));
        memset(arrays->values + arrays->capacity, 0, sizeof(int) * 16);
        arrays->capacity += 16;
    }

    adjustHeapUp(arrays, arrays->length, value);
    ++arrays->length;
}

void erase(ArrayNode *arrays, int index) {
    if (index >= 0 && index < arrays->length) {
        --arrays->length;
        adjustHeapDown(arrays, index, arrays->values[arrays->length]);
    }
}

void set(ArrayNode *arrays, int index, int value) {
    if (index >= 0 && index < arrays->length && value != arrays->values[index]) {
        if (value < arrays->values[index]) {
            adjustHeapUp(arrays, index, value);
        } else {
            adjustHeapDown(arrays, index, value);
        }
    }
}

int get(ArrayNode arrays, int index) {
    if (index >= 0 && index < arrays.length) {
        return arrays.values[index];
    }
    return 1 << 31;
}

void clear(ArrayNode *arrays) {
    memset(arrays->values, 0, sizeof(int) * arrays->capacity);
    arrays->length = 0;
}

static void adjustHeapUp(ArrayNode *arrays, int child, int value) {
    while (child > 0) {
        int parent = (child - 1) >> 1;
        if (arrays->values[parent] <= value) {
            break;
        }
        arrays->values[child] = arrays->values[parent];
        child = parent;
    }
    arrays->values[child] = value;
}

static void adjustHeapDown(ArrayNode *arrays, int parent, int value) {
    while (1) {
        int child = (parent << 1) + 1;
        if (child >= arrays->length) {
            break;
        }

        if (child < arrays->length - 1 && arrays->values[child] > arrays->values[child + 1]) {
            ++child;
        }
        if (arrays->values[child] >= value) {
            break;
        }
        arrays->values[parent] = arrays->values[child];
        parent = child;
    }
    arrays->values[parent] = value;
}
