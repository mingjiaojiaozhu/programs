#include <stdio.h>

int binarySearch(int *nums, int length, int target) {
    int start = 0;
    int end = length - 1;
    while (start <= end) {
        int middle = start + ((end - start) >> 1);
        if (target == nums[middle]) {
            return middle;
        }

        if (target < nums[middle]) {
            end = middle - 1;
        } else {
            start = middle + 1;
        }
    }
    return -1;
}
