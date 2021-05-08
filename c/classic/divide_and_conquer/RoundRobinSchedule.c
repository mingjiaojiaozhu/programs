#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
    int *values;
    int length;
} ArrayNode;

typedef struct {
    ArrayNode *values;
    int length;
} DoublyArrayNode;

static void schedule(int size, int startRow, int startCol, DoublyArrayNode *result);

void roundRobinSchedule(int k, DoublyArrayNode *result) {
    int size = (int) pow((double) 2, k);
    result->values = (ArrayNode *) malloc(sizeof(ArrayNode) * size);
    for (int i = 0; i < size; ++i) {
        result->values[i].values = (int *) malloc(sizeof(int) * size);
        for (int j = 0; j < size; ++j) {
            result->values[i].values[j] = i;
        }
        result->values[i].length = size;
    }
    result->length = size;
    schedule(size, 0, 0, result);
}

static void schedule(int size, int startRow, int startCol, DoublyArrayNode *result) {
    size >>= 1;
    if (size > 1) {
        schedule(size, startRow, startCol, result);
        schedule(size, startRow + size, startCol, result);
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result->values[startRow + size + i].values[startCol + size + j] = result->values[startRow + i].values[startCol + j];
            result->values[startRow + i].values[startCol + size + j] = result->values[startRow + size + i].values[startCol + j];
        }
    }
}
