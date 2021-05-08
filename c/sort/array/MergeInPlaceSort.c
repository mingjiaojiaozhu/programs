#include <stdio.h>

static void sort(int *nums, int start, int end);
static void merge(int *nums, int start, int middle, int end);
static void reverse(int *start, int *end);

void mergeInPlaceSort(int *nums, int length) {
    sort(nums, 0, length - 1);
}

static void sort(int *nums, int start, int end) {
    if (start >= end) {
        return;
    }

    int middle = start + ((end - start) >> 1);
    sort(nums, start, middle);
    sort(nums, middle + 1, end);

    if (nums[middle] > nums[middle + 1]) {
        merge(nums, start, middle, end);
    }
}

static void merge(int *nums, int start, int middle, int end) {
    int left = start;
    int right = middle + 1;
    while (left < right && right <= end) {
        while (left < right && nums[left] <= nums[right]) {
            ++left;
        }

        int index = right;
        while (right <= end && nums[right] < nums[left]) {
            ++right;
        }

        reverse(nums + left, nums + index - 1);
        reverse(nums + index, nums + right - 1);
        reverse(nums + left, nums + right - 1);

        left += right - index;
    }
}

static void reverse(int *start, int *end) {
    while (start < end) {
        *start ^= *end;
        *end ^= *start;
        *start ^= *end;

        ++start;
        --end;
    }
}
