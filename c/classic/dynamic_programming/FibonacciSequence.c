#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *values;
    int length;
} ArrayNode;

void fibonacciSequence(int num, ArrayNode *result) {
    result->values = (int *) malloc(sizeof(int) * num);
    result->values[0] = 1;
    result->values[1] = 1;
    for (int i = 2; i < num; ++i) {
        result->values[i] = result->values[i - 1] + result->values[i - 2];
    }
    result->length = num;
}
