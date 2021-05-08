#include <stdio.h>

void bubbleSort(int *nums, int length) {
    int border = length - 1;
    for (int i = 0; i < length; ++i) {
        int flag = 0;
        int index = 0;
        for (int j = 0; j < border; ++j) {
            if (nums[j + 1] < nums[j]) {
                nums[j] ^= nums[j + 1];
                nums[j + 1] ^= nums[j];
                nums[j] ^= nums[j + 1];

                flag = 1;
                index = j;
            }
        }

        if (!flag) {
            break;
        }
        border = index;
    }
}
