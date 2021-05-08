#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *values;
    int length;
} ArrayNode;

static int search(int *nums, int start, int end, int k);
static int getMedian(int *nums, int start, int end);
static int getPartition(int *nums, int start, int end);
static void swap(int *p, int *q);
static int cmp(const void *p, const void *q);

void bfprtSelect(int *nums, int length, int k, ArrayNode *result) {
    search(nums, 0, length - 1, k);
    result->values = (int *) malloc(sizeof(int) * k);
    memcpy(result->values, nums, sizeof(int) * k);
    result->length = k;
}

static int search(int *nums, int start, int end, int k) {
    int median = getMedian(nums, start, end);
    int partition = getPartition(nums, median, end);
    if (k == partition - start + 1) {
        return partition;
    }

    if (k < partition - start + 1) {
        return search(nums, start, partition - 1, k);
    }
    return search(nums, partition + 1, end, k - (partition - start + 1));
}

static int getMedian(int *nums, int start, int end) {
    if (end - start < 5) {
        qsort(nums + start, end - start + 1, sizeof(int), cmp);
        return start + ((end - start) >> 1);
    }

    int index = start;
    int left = start;
    int right = end - 4;
    while (left <= right) {
        qsort(nums + left, 5, sizeof(int), cmp);
        swap(&nums[index], &nums[left + 2]);

        left += 5;
        ++index;
    }
    return search(nums, start, index - 1, ((index - start) >> 1) + 1);
}

static int getPartition(int *nums, int start, int end) {
    int pivot = nums[start];
    int left = start;
    int right = end;
    while (left < right) {
        while (left < right && nums[right] > pivot) {
            --right;
        }
        while (left < right && nums[left] <= pivot) {
            ++left;
        }

        if (left < right) {
            swap(&nums[left], &nums[right]);
        }
    }
    swap(&nums[start], &nums[left]);
    return left;
}

static void swap(int *p, int *q) {
    if (*p != *q) {
        *p ^= *q;
        *q ^= *p;
        *p ^= *q;
    }
}

static int cmp(const void *p, const void *q) {
    return *((int *) p) - *((int *) q);
}
