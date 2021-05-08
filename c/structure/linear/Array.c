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

void add(ArrayNode *arrays, int index, int value) {
    if (index < 0 || index > arrays->length) {
        return;
    }

    if (arrays->length >= arrays->capacity) {
        arrays->values = (int *) realloc(arrays->values, sizeof(int) * (arrays->capacity + 16));
        memset(arrays->values + arrays->capacity, 0, sizeof(int) * 16);
        arrays->capacity += 16;
    }

    for (int i = arrays->length - 1; i >= index; --i) {
        arrays->values[i + 1] = arrays->values[i];
    }
    arrays->values[index] = value;
    ++arrays->length;
}

void addHead(ArrayNode *arrays, int value) {
    if (arrays->length >= arrays->capacity) {
        arrays->values = (int *) realloc(arrays->values, sizeof(int) * (arrays->capacity + 16));
        memset(arrays->values + arrays->capacity, 0, sizeof(int) * 16);
        arrays->capacity += 16;
    }

    for (int i = arrays->length - 1; i >= 0; --i) {
        arrays->values[i + 1] = arrays->values[i];
    }
    arrays->values[0] = value;
    ++arrays->length;
}

void addTail(ArrayNode *arrays, int value) {
    if (arrays->length >= arrays->capacity) {
        arrays->values = (int *) realloc(arrays->values, sizeof(int) * (arrays->capacity + 16));
        memset(arrays->values + arrays->capacity, 0, sizeof(int) * 16);
        arrays->capacity += 16;
    }

    arrays->values[arrays->length] = value;
    ++arrays->length;
}

void erase(ArrayNode *arrays, int index) {
    if (index < 0 || index >= arrays->length) {
        return;
    }

    for (int i = index + 1; i < arrays->length; ++i) {
        arrays->values[i - 1] = arrays->values[i];
    }
    --arrays->length;
}

void eraseHead(ArrayNode *arrays) {
    if (!arrays->length) {
        return;
    }

    for (int i = 1; i < arrays->length; ++i) {
        arrays->values[i - 1] = arrays->values[i];
    }
    --arrays->length;
}

void eraseTail(ArrayNode *arrays) {
    if (arrays->length) {
        --arrays->length;
    }
}

void set(ArrayNode *arrays, int index, int value) {
    if (index >= 0 && index < arrays->length) {
        arrays->values[index] = value;
    }
}

int get(ArrayNode arrays, int index) {
    if (index >= 0 && index < arrays.length) {
        return arrays.values[index];
    }
    return 1 << 31;
}

void reverse(ArrayNode *arrays) {
    int start = 0;
    int end = arrays->length - 1;
    while (start < end) {
        arrays->values[start] ^= arrays->values[end];
        arrays->values[end] ^= arrays->values[start];
        arrays->values[start] ^= arrays->values[end];

        ++start;
        --end;
    }
}

void clear(ArrayNode *arrays) {
    memset(arrays->values, 0, sizeof(int) * arrays->capacity);
    arrays->length = 0;
}
