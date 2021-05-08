#include <stdio.h>

static void swap(int *p, int *q);

void selectionSort(int *nums, int length) {
    int start = 0;
    int end = length - 1;
    while (start <= end) {
        int maxIndex = start;
        int minIndex = start;
        for (int i = start + 1; i <= end; ++i) {
            if (nums[maxIndex] < nums[i]) {
                maxIndex = i;
            } else if (nums[minIndex] > nums[i]) {
                minIndex = i;
            }
        }

        swap(&nums[minIndex], &nums[start]);
        if (maxIndex == start) {
            maxIndex = minIndex;
        }
        swap(&nums[maxIndex], &nums[end]);

        ++start;
        --end;
    }
}

static void swap(int *p, int *q) {
    if (*p != *q) {
        *p ^= *q;
        *q ^= *p;
        *p ^= *q;
    }
}
