#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    int *values;
    int length;
} ArrayNode;

void insideOut(int *nums, int length, ArrayNode *result) {
    srand((unsigned int) time(NULL));
    result->values = (int *) malloc(sizeof(int) * length);
    memcpy(result->values, nums, sizeof(int) * length);
    result->length = length;
    for (int i = 0; i < length; ++i) {
        int index = rand() % (i + 1);
        result->values[i] = result->values[index];
        result->values[index] = nums[i];
    }
}
