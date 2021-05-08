#include <stdio.h>

int blockingSearch(int *nums, int length, int **blocks, int blockSize, int target) {
    int start = 0;
    int end = blockSize - 1;
    while (start <= end) {
        int middle = start + ((end - start) >> 1);
        if (target <= blocks[middle][2]) {
            end = middle - 1;
        } else {
            start = middle + 1;
        }
    }

    if (start >= blockSize) {
        return -1;
    }

    for (int i = blocks[start][0]; i <= blocks[start][1]; ++i) {
        if (target == nums[i]) {
            return i;
        }
    }
    return -1;
}
