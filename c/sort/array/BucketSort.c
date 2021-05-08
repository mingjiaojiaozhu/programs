#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *values;
    int length;
} ArrayNode;

static int cmp(const void *p, const void *q);

void bucketSort(int *nums, int length) {
    int maxValue = nums[0];
    int minValue = nums[0];
    for (int i = 1; i < length; ++i) {
        if (maxValue < nums[i]) {
            maxValue = nums[i];
        }
        if (minValue > nums[i]) {
            minValue = nums[i];
        }
    }

    int size = (maxValue - minValue) / 10 + 1;
    ArrayNode *buckets = (ArrayNode *) malloc(sizeof(ArrayNode) * size);
    for (int i = 0; i < size; ++i) {
        buckets[i].values = (int *) malloc(sizeof(int) * length);
        memset(buckets[i].values, 0, sizeof(int) * length);
        buckets[i].length = 0;
    }
    for (int i = 0; i < length; ++i) {
        int value = nums[i];
        int index = (value - minValue) / 10;
        buckets[index].values[buckets[index].length] = value;
        ++buckets[index].length;
    }

    int index = 0;
    for (int i = 0; i < size; ++i) {
        qsort(buckets[i].values, buckets[i].length, sizeof(int), cmp);

        for (int j = 0; j < buckets[i].length; ++j) {
            nums[index] = buckets[i].values[j];
            ++index;
        }
    }
}

static int cmp(const void *p, const void *q) {
    return *((int *) p) - *((int *) q);
}
