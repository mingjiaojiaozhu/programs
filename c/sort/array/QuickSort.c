#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static void sort(int *nums, int start, int end);
static int getPartition(int *nums, int start, int end);
static void swap(int *p, int *q);

void quickSort(int *nums, int length) {
    srand((unsigned int) time(NULL));
    sort(nums, 0, length - 1);
}

static void sort(int *nums, int start, int end) {
    if (start < end) {
        int partition = getPartition(nums, start, end);
        sort(nums, start, partition - 1);
        sort(nums, partition + 1, end);
    }
}

static int getPartition(int *nums, int start, int end) {
    int index = start + rand() % (end - start + 1);
    swap(&nums[index], &nums[end]);
    int pivot = nums[end];

    int left = start;
    int right = end;
    while (left < right) {
        while (left < right && nums[left] < pivot) {
            ++left;
        }
        while (left < right && nums[right] >= pivot) {
            --right;
        }

        if (left < right) {
            swap(&nums[left], &nums[right]);
        }
    }
    swap(&nums[left], &nums[end]);
    return left;
}

static void swap(int *p, int *q) {
    if (*p != *q) {
        *p ^= *q;
        *q ^= *p;
        *p ^= *q;
    }
}
