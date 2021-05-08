#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int min(int i, int j);

int knapsackOfMultiple(int *weights, int *values, int *nums, int length, int target) {
    int *result = (int *) malloc(sizeof(int) * (target + 1));
    memset(result, 0, sizeof(int) * (target + 1));
    for (int i = 0; i < length; ++i) {
        int weight = weights[i];
        int value = values[i];
        int num = nums[i];
        for (int j = target; j >= weight; --j) {
            for (int k = 0; k <= min(num, j / weight); ++k) {
                int pivot = result[j - k * weight] + k * value;
                if (result[j] < pivot) {
                    result[j] = pivot;
                }
            }
        }
    }
    return result[target];
}

static int min(int i, int j) {
    int aux = ~((i > j) ? 1 : 0) + 1;
    return (i & ~aux) | (j & aux);
}
