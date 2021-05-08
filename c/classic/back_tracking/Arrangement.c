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

static void search(int *nums, int length, int k, int start, DoublyArrayNode *result);
static void swap(int *p, int *q);

void arrangement(int *nums, int length, int k, DoublyArrayNode *result) {
    result->values = (ArrayNode *) malloc(sizeof(ArrayNode) * 64);
    for (int i = 0; i < 64; ++i) {
        result->values[i].values = NULL;
        result->values[i].length = 0;
    }
    result->length = 0;
    result->capacity = 64;
    search(nums, length, k, 0, result);
}

static void search(int *nums, int length, int k, int start, DoublyArrayNode *result) {
    if (k == start) {
        if (result->length >= result->capacity) {
            result->values = (ArrayNode *) realloc(result->values, sizeof(ArrayNode) * (result->capacity + 16));
            for (int i = result->capacity; i < result->capacity + 16; ++i) {
                result->values[i].values = NULL;
                result->values[i].length = 0;
            }
            result->capacity += 16;
        }
        result->values[result->length].values = (int *) malloc(sizeof(int) * k);
        memcpy(result->values[result->length].values, nums, sizeof(int) * k);
        result->values[result->length].length = k;
        ++result->length;
        return;
    }

    search(nums, length, k, start + 1, result);
    for (int i = start + 1; i < length; ++i) {
        swap(&nums[start], &nums[i]);
        search(nums, length, k, start + 1, result);
        swap(&nums[start], &nums[i]);
    }
}

static void swap(int *p, int *q) {
    *p ^= *q;
    *q ^= *p;
    *p ^= *q;
}
