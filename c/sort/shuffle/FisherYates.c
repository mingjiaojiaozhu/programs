#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    int *values;
    int length;
} ArrayNode;

void fisherYates(int *nums, int length, ArrayNode *result) {
    srand((unsigned int) time(NULL));
    result->values = (int *) malloc(sizeof(int) * length);
    memset(result->values, 0, sizeof(int) * length);
    result->length = 0;
    for (int i = length - 1; i >= 0; --i) {
        int index = rand() % (i + 1);
        result->values[result->length] = nums[index];
        ++result->length;
        for (int j = index + 1; j <= i; ++j) {
            nums[j - 1] = nums[j];
        }
    }
}
