#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *values;
    int length;
} ArrayNode;

typedef struct {
    ArrayNode *values;
    int length;
    int capacity;
} DoublyArrayNode;

static void search(int *nums, int length, int start, ArrayNode *aux, DoublyArrayNode *result);

void subcollection(int *nums, int length, DoublyArrayNode *result) {
    result->values = (ArrayNode *) malloc(sizeof(ArrayNode) * 64);
    for (int i = 0; i < 64; ++i) {
        result->values[i].values = NULL;
        result->values[i].length = 0;
    }
    result->length = 0;
    result->capacity = 64;
    ArrayNode *aux = (ArrayNode *) malloc(sizeof(ArrayNode));
    aux->values = (int *) malloc(sizeof(int) * length);
    memset(aux->values, 0, sizeof(int) * length);
    aux->length = 0;
    search(nums, length, 0, aux, result);
}

static void search(int *nums, int length, int start, ArrayNode *aux, DoublyArrayNode *result) {
    if (result->length >= result->capacity) {
        result->values = (ArrayNode *) realloc(result->values, sizeof(ArrayNode) * (result->capacity + 16));
        for (int i = result->capacity; i < result->capacity + 16; ++i) {
            result->values[i].values = NULL;
            result->values[i].length = 0;
        }
        result->capacity += 16;
    }
    result->values[result->length].values = (int *) malloc(sizeof(int) * aux->length);
    memcpy(result->values[result->length].values, aux->values, sizeof(int) * aux->length);
    result->values[result->length].length = aux->length;
    ++result->length;

    for (int i = start; i < length; ++i) {
        aux->values[aux->length] = nums[i];
        ++aux->length;
        search(nums, length, i + 1, aux, result);
        --aux->length;
    }
}
