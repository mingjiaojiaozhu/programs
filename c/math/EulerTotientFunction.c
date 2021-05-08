#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *values;
    int length;
} ArrayNode;

void eulerTotientFunction(int num, ArrayNode *result) {
    int *isPrime = (int *) malloc(sizeof(int) * num);
    for (int i = 0; i < num; ++i) {
        isPrime[i] = 1;
    }
    int *primes = (int *) malloc(sizeof(int) * num);
    memset(primes, 0, sizeof(int) * num);
    int index = 0;

    result->values = (int *) malloc(sizeof(int) * num);
    memset(result->values, 0, sizeof(int) * num);
    result->length = num;
    for (int i = 2; i <= num; ++i) {
        if (isPrime[i - 1]) {
            primes[index] = i;
            ++index;
            result->values[i - 1] = i - 1;
        }

        for (int j = 0; j < index; ++j) {
            int value = primes[j];
            if (value > num / i) {
                break;
            }

            isPrime[i * value - 1] = 0;
            if (!(i % value)) {
                result->values[i * value - 1] = result->values[i - 1] * value;
                break;
            } else {
                result->values[i * value - 1] = result->values[i - 1] * (value - 1);
            }
        }
    }
}
