#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *values;
    int length;
} ArrayNode;

void radixSort(int *nums, int length) {
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

    ArrayNode *buckets = (ArrayNode *) malloc(sizeof(ArrayNode) * 10);
    for (int i = 0; i < 10; ++i) {
        buckets[i].values = (int *) malloc(sizeof(int) * length);
        memset(buckets[i].values, 0, sizeof(int) * length);
        buckets[i].length = 0;
    }

    int diff = maxValue - minValue;
    for (int gap = 1; gap <= diff; gap *= 10) {
        for (int i = 0; i < 10; ++i) {
            buckets[i].length = 0;
        }
        for (int i = 0; i < length; ++i) {
            int value = nums[i];
            int index = ((value - minValue) / gap) % 10;
            buckets[index].values[buckets[index].length] = value;
            ++buckets[index].length;
        }

        int index = 0;
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < buckets[i].length; ++j) {
                nums[index] = buckets[i].values[j];
                ++index;
            }
        }
    }
}
