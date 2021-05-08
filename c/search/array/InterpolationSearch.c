#include <stdio.h>

int interpolationSearch(int *nums, int length, int target) {
    int start = 0;
    int end = length - 1;
    while (start < end && nums[start] != nums[end]) {
        int middle = start + (target - nums[start]) * (end - start) / (nums[end] - nums[start]);
        if (middle < start || middle > end) {
            return -1;
        }

        if (target == nums[middle]) {
            return middle;
        }

        if (target < nums[middle]) {
            end = middle - 1;
        } else {
            start = middle + 1;
        }
    }
    return (start < length && target == nums[start]) ? start : -1;
}
