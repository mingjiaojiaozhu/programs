#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *values;
    int length;
} ArrayNode;

void gcd(int num1, int num2, ArrayNode *result) {
    if (!num2) {
        result->values = (int *) malloc(sizeof(int) * 3);
        result->values[0] = num1;
        result->values[1] = 1;
        result->values[2] = 0;
        result->length = 3;
        return;
    }

    gcd(num2, num1 % num2, result);
    int aux = result->values[1] - result->values[2] * (num1 / num2);
    result->values[1] = result->values[2];
    result->values[2] = aux;
}
