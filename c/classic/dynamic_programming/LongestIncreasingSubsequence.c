#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int longestIncreasingSubsequence(int *values, int length) {
    int *result = (int *) malloc(sizeof(int) * length);
    memset(result, 0, sizeof(int) * length);
    result[0] = 1;
    for (int i = 1; i < length; ++i) {
        result[i] = 1;
        for (int j = 0; j < i; ++j) {
            if (values[i] > values[j] && result[i] < result[j] + 1) {
                result[i] = result[j] + 1;
            }
        }
    }

    int maxValue = result[0];
    for (int i = 1; i < length; ++i) {
        if (maxValue < result[i]) {
            maxValue = result[i];
        }
    }
    return maxValue;
}
