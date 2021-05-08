#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *values;
    int length;
    int capacity;
} ArrayNode;

int fibonacciSearch(int *nums, int length, int target) {
    ArrayNode *fibonacci = (ArrayNode *) malloc(sizeof(ArrayNode));
    fibonacci->values = (int *) malloc(sizeof(int) * 64);
    memset(fibonacci->values, 0, sizeof(int) * 64);
    fibonacci->values[0] = 1;
    fibonacci->values[1] = 1;
    fibonacci->length = 2;
    fibonacci->capacity = 64;

    int index = 1;
    while (length > fibonacci->values[index] - 1) {
        ++index;
        if (fibonacci->length >= fibonacci->capacity) {
            fibonacci->values = (int *) realloc(fibonacci->values, sizeof(int) * (fibonacci->capacity + 16));
            memset(fibonacci->values + fibonacci->capacity, 0, sizeof(int) * 16);
            fibonacci->capacity += 16;
        }
        fibonacci->values[fibonacci->length] = fibonacci->values[index - 1] + fibonacci->values[index - 2];
        ++fibonacci->length;
    }

    int *aux = (int *) malloc(sizeof(int) * fibonacci->values[index]);
    memcpy(aux, nums, sizeof(int) * length);
    for (int i = length; i < fibonacci->values[index]; ++i) {
        aux[i] = nums[length - 1];
    }

    int start = 0;
    int end = length - 1;
    while (start <= end) {
        int middle = start + fibonacci->values[index - 1] - 1;
        if (target == aux[middle]) {
            return (middle >= length) ? length - 1 : middle;
        }

        if (target < aux[middle]) {
            end = middle - 1;
            --index;
        } else {
            start = middle + 1;
            index -= 2;
        }
    }
    return -1;
}
