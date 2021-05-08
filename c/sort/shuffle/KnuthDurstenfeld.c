#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void knuthDurstenfeld(int *nums, int length) {
    srand((unsigned int) time(NULL));
    for (int i = length - 1; i > 0; --i) {
        int index = rand() % (i + 1);
        if (index != i) {
            nums[index] ^= nums[i];
            nums[i] ^= nums[index];
            nums[index] ^= nums[i];
        }
    }
}
