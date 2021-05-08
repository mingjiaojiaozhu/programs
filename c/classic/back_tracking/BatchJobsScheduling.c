#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *values;
    int length;
} ArrayNode;

static int search(int **values, int length, int start, int *ends, int minValue, int *aux, ArrayNode *result);
static void swap(int *p, int *q);
static int max(int i, int j);

void batchJobsScheduling(int **values, int length, ArrayNode *result) {
    result->values = (int *) malloc(sizeof(int) * length);
    memset(result->values, 0, sizeof(int) * length);
    result->length = length;
    int *aux = (int *) malloc(sizeof(int) * length);
    for (int i = 0; i < length; ++i) {
        aux[i] = i;
    }
    int *ends = (int *) malloc(sizeof(int) * 3);
    memset(ends, 0, sizeof(int) * 3);
    search(values, length, 0, ends, ~(1 << 31), aux, result);
}

static int search(int **values, int length, int start, int *ends, int minValue, int *aux, ArrayNode *result) {
    if (start == length) {
        memcpy(result->values, aux, sizeof(int) * result->length);
        return ends[2];
    }

    for (int i = start; i < length; ++i) {
        ends[0] += values[aux[i]][0];
        int pivot = ends[1];
        ends[1] = max(ends[0], ends[1]) + values[aux[i]][1];
        ends[2] += ends[1];
        if (ends[2] < minValue) {
            swap(&aux[start], &aux[i]);
            minValue = search(values, length, start + 1, ends, minValue, aux, result);
            swap(&aux[start], &aux[i]);
        }
        ends[0] -= values[aux[i]][0];
        ends[2] -= ends[1];
        ends[1] = pivot;
    }
    return minValue;
}

static void swap(int *p, int *q) {
    if (*p != *q) {
        *p ^= *q;
        *q ^= *p;
        *p ^= *q;
    }
}

static int max(int i, int j) {
    int aux = ~((i > j) ? 1 : 0) + 1;
    return (i & aux) | (j & ~aux);
}
