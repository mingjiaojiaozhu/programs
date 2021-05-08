#include <stdio.h>
#include <stdlib.h>

int coinChange(int *values, int length, int target) {
    int *result = (int *) malloc(sizeof(int) * (target + 1));
    for (int i = 1; i <= target; ++i) {
        result[i] = ~(1 << 31);
    }
    result[0] = 0;
    for (int i = 0; i <= target; ++i) {
        for (int j = 0; j < length; ++j) {
            if (i >= values[j]) {
                int pivot = result[i - values[j]] + 1;
                if (result[i] > pivot) {
                    result[i] = pivot;
                }
            }
        }
    }
    return (result[target] <= target) ? result[target] : -1;
}
