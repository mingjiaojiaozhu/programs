#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *values;
    int length;
} ArrayNode;

static void move(int size, ArrayNode *values1, ArrayNode *values2, ArrayNode *values3);

void hanoi(ArrayNode *values1, ArrayNode *values2, ArrayNode *values3) {
    values2->values = (int *) malloc(sizeof(int) * values1->length);
    values3->values = (int *) malloc(sizeof(int) * values1->length);
    move(values1->length, values1, values2, values3);
}

static void move(int size, ArrayNode *values1, ArrayNode *values2, ArrayNode *values3) {
    --size;
    if (!size) {
        values3->values[values3->length] = values1->values[values1->length - 1];
        ++values3->length;
        --values1->length;
        return;
    }

    move(size, values1, values3, values2);
    values3->values[values3->length] = values1->values[values1->length - 1];
    ++values3->length;
    --values1->length;
    move(size, values2, values1, values3);
}
