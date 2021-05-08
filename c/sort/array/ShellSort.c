#include <stdio.h>

void shellSort(int *nums, int length) {
    int gap = 1;
    while (gap < length / 3) {
        gap = gap * 3 + 1;
    }

    while (gap > 0) {
        for (int i = gap; i < length; ++i) {
            int pivot = nums[i];
            int index = i - gap;
            while (index >= 0 && nums[index] > pivot) {
                nums[index + gap] = nums[index];
                index -= gap;
            }
            nums[index + gap] = pivot;
        }
        gap /= 3;
    }
}
