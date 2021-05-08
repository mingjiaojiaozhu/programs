#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *values;
    int length;
} ArrayNode;

static void enqueue(ArrayNode *queue, int value);
static void dequeue(ArrayNode *queue);

void heapSelect(int *nums, int length, int k, ArrayNode *result) {
    result->values = (int *) malloc(sizeof(int) * k);
    memset(result->values, 0, sizeof(int) * k);
    result->length = 0;

    for (int i = 0; i < k; ++i) {
        enqueue(result, nums[i]);
    }
    for (int i = k; i < length; ++i) {
        if (nums[i] < result->values[0]) {
            dequeue(result);
            enqueue(result, nums[i]);
        }
    }
}

static void enqueue(ArrayNode *queue, int value) {
    int child = queue->length;
    while (child > 0) {
        int parent = (child - 1) >> 1;
        if (queue->values[parent] >= value) {
            break;
        }
        queue->values[child] = queue->values[parent];
        child = parent;
    }
    queue->values[child] = value;
    ++queue->length;
}

static void dequeue(ArrayNode *queue) {
    --queue->length;
    int pivot = queue->values[queue->length];
    int parent = 0;
    while (1) {
        int child = (parent << 1) + 1;
        if (child >= queue->length) {
            break;
        }

        if (child < queue->length - 1 && queue->values[child] < queue->values[child + 1]) {
            ++child;
        }
        if (queue->values[child] <= pivot) {
            break;
        }
        queue->values[parent] = queue->values[child];
        parent = child;
    }
    queue->values[parent] = pivot;
}
