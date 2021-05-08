#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *values;
    int head;
    int tail;
    int capacity;
} ArrayNode;

void create(ArrayNode *arrays) {
    arrays->values = (int *) malloc(sizeof(int) * 64);
    memset(arrays->values, 0, sizeof(int) * 64);
    arrays->head = 0;
    arrays->tail = 0;
    arrays->capacity = 64;
}

int isEmpty(ArrayNode arrays) {
    return (arrays.head == arrays.tail) ? 1 : 0;
}

void enqueue(ArrayNode *arrays, int value) {
    if ((arrays->tail + 1) % arrays->capacity == arrays->head) {
        int *aux = (int *) malloc(sizeof(int) * (arrays->capacity + 16));
        if (arrays->head < arrays->tail) {
            memcpy(aux, arrays->values + arrays->head, sizeof(int) * (arrays->tail - arrays->head));
        } else {
            memcpy(aux, arrays->values + arrays->head, sizeof(int) * (arrays->capacity - arrays->head));
            memcpy(aux + arrays->capacity - arrays->head, arrays->values, sizeof(int) * (arrays->tail));
        }
        memset(aux + arrays->capacity, 0, sizeof(int) * 16);
        arrays->values = aux;
        arrays->head = 0;
        arrays->tail = arrays->capacity - 1;
        arrays->capacity += 16;
    }

    arrays->values[arrays->tail] = value;
    arrays->tail = (arrays->tail + 1) % arrays->capacity;
}

int dequeue(ArrayNode *arrays) {
    if (arrays->head != arrays->tail) {
        int value = arrays->values[arrays->head];
        arrays->head = (arrays->head + 1) % arrays->capacity;
        return value;
    }
    return 1 << 31;
}

void clear(ArrayNode *arrays) {
    memset(arrays->values, 0, sizeof(int) * arrays->capacity);
    arrays->head = 0;
    arrays->tail = 0;
}
