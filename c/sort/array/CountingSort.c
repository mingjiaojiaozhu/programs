#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void countingSort(int *nums, int length) {
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

    int size = maxValue - minValue + 1;
    int *buckets = (int *) malloc(sizeof(int) * size);
    memset(buckets, 0, sizeof(int) * size);
    for (int i = 0; i < length; ++i) {
        ++buckets[nums[i] - minValue];
    }
    for (int i = 1; i < size; ++i) {
        buckets[i] += buckets[i - 1];
    }

    int *aux = (int *) malloc(sizeof(int) * length);
    memcpy(aux, nums, sizeof(int) * length);
    for (int i = length - 1; i >= 0; --i) {
        int index = aux[i] - minValue;
        nums[buckets[index] - 1] = aux[i];
        --buckets[index];
    }
}
