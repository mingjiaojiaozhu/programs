#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *values;
    int length;
} ArrayNode;

static int search(int num, int count, int start, int index, int *ends, int maxValue, int *aux, ArrayNode *result);

void continuousPostage(int num, int count, ArrayNode *result) {
    result->values = (int *) malloc(sizeof(int) * num);
    memset(result->values, 0, sizeof(int) * num);
    result->length = num;
    int *aux = (int *) malloc(sizeof(int) * (num + 1));
    memset(aux, 0, sizeof(int) * (num + 1));
    aux[1] = 1;
    int *ends = (int *) malloc(sizeof(int) * ((num * count) << 6));
    for (int i = 1; i < (num * count) << 6; ++i) {
        ends[i] = ~(1 << 31);
    }
    ends[0] = 0;
    search(num, count, 1, 1, ends, 0, aux, result);
}

static int search(int num, int count, int start, int index, int *ends, int maxValue, int *aux, ArrayNode *result) {
    for (int i = 0; i <= aux[start - 1] * (count - 1); ++i) {
        if (ends[i] < count) {
            for (int j = 1; j <= count - ends[i]; ++j) {
                if (ends[i + aux[start] * j] > ends[i] + j) {
                    ends[i + aux[start] * j] = ends[i] + j;
                }
            }
        }
    }
    while (ends[index] < ~(1 << 31)) {
        ++index;
    }

    if (start == num) {
        if (maxValue < index - 1) {
            memcpy(result->values, aux + 1, sizeof(int) * result->length);
            maxValue = index - 1;
        }
        return maxValue;
    }

    int *pivot = (int *) malloc(sizeof(int) * ((num * count) << 6));
    memcpy(pivot, ends, sizeof(int) * ((num * count) << 6));
    for (int i = aux[start] + 1; i <= index; ++i) {
        if (ends[index - i] < count) {
            aux[start + 1] = i;
            maxValue = search(num, count, start + 1, index + 1, ends, maxValue, aux, result);
            memcpy(ends, pivot, sizeof(int) * ((num * count) << 6));
        }
    }
    return maxValue;
}
