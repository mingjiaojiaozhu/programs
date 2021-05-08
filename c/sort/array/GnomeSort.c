#include <stdio.h>

void gnomeSort(int *nums, int length) {
    int index = 0;
    while (index < length) {
        if (0 == index || nums[index - 1] <= nums[index]) {
            ++index;
        } else {
            nums[index] ^= nums[index - 1];
            nums[index - 1] ^= nums[index];
            nums[index] ^= nums[index - 1];

            --index;
        }
    }
}
