#include <stdio.h>

static void reverse(int *start, int *end);

void pancakeSort(int *nums, int length) {
    for (int i = length - 1; i > 0; --i) {
        int maxIndex = 0;
        for (int j = 1; j <= i; ++j) {
            if (nums[maxIndex] < nums[j]) {
                maxIndex = j;
            }
        }
        reverse(nums, nums + maxIndex);
        reverse(nums, nums + i);
    }
}

static void reverse(int *start, int *end) {
    while (start < end) {
        *start ^= *end;
        *end ^= *start;
        *start ^= *end;

        ++start;
        --end;
    }
}
