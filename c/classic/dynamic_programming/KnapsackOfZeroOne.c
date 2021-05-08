#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int knapsackOfZeroOne(int *weights, int *values, int length, int target) {
    int *result = (int *) malloc(sizeof(int) * (target + 1));
    memset(result, 0, sizeof(int) * (target + 1));
    for (int i = 0; i < length; ++i) {
        int weight = weights[i];
        int value = values[i];
        for (int j = target; j >= weight; --j) {
            int pivot = result[j - weight] + value;
            if (result[j] < pivot) {
                result[j] = pivot;
            }
        }
    }
    return result[target];
}
