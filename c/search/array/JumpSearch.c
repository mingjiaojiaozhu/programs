#include <stdio.h>
#include <math.h>

static int min(int i, int j);

int jumpSearch(int *nums, int length, int target) {
    int step = (int) sqrt((double) length);
    int border = step;
    while (border < length && target > nums[border]) {
        border += step;
    }

    for (int i = border - step; i < min(border + 1, length); ++i) {
        if (target == nums[i]) {
            return i;
        }
    }
    return -1;
}

static int min(int i, int j) {
    int aux = ~((i > j) ? 1 : 0) + 1;
    return (i & ~aux) | (j & aux);
}
