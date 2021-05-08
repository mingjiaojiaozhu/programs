#include <stdio.h>

static void swap(int *p, int *q);

void cocktailSort(int *nums, int length) {
    int start = 0;
    int end = length - 1;
    while (start < end) {
        int flag = 0;
        int index = 0;
        for (int i = start; i < end; ++i) {
            if (nums[i + 1] < nums[i]) {
                swap(&nums[i], &nums[i + 1]);

                flag = 1;
                index = i;
            }
        }

        if (!flag) {
            break;
        }
        end = index;

        flag = 0;
        index = 0;
        for (int i = end; i > start; --i) {
            if (nums[i - 1] > nums[i]) {
                swap(&nums[i], &nums[i - 1]);

                flag = 1;
                index = i;
            }
        }

        if (!flag) {
            break;
        }
        start = index;
    }
}

static void swap(int *p, int *q) {
    *p ^= *q;
    *q ^= *p;
    *p ^= *q;
}
