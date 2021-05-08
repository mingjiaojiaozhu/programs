#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *values;
    int length;
} ArrayNode;

void eulerSieve(int num, ArrayNode *result) {
    int *isPrime = (int *) malloc(sizeof(int) * num);
    for (int i = 0; i < num; ++i) {
        isPrime[i] = 1;
    }

    result->values = (int *) malloc(sizeof(int) * num);
    memset(result->values, 0, sizeof(int) * num);
    result->length = 0;
    for (int i = 2; i <= num; ++i) {
        if (isPrime[i - 1]) {
            result->values[result->length] = i;
            ++result->length;
        }

        for (int j = 0; j < result->length; ++j) {
            int value = result->values[j];
            if (value > num / i) {
                break;
            }

            isPrime[i * value - 1] = 0;
            if (!(i % value)) {
                break;
            }
        }
    }
}
