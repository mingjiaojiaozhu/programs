#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    int *values;
    int length;
} ArrayNode;

static void search(int *nums, int start, int end, int k);
static int getPartition(int *nums, int start, int end);
static void swap(int *p, int *q);

void quickSelect(int *nums, int length, int k, ArrayNode *result) {
    srand((unsigned int) time(NULL));
    search(nums, 0, length - 1, k);
    result->values = (int *) malloc(sizeof(int) * k);
    memcpy(result->values, nums, sizeof(int) * k);
    result->length = k;
}

static void search(int *nums, int start, int end, int k) {
    int partition = getPartition(nums, start, end);
    if (k == partition - start + 1) {
        return;
    }

    if (k < partition - start + 1) {
        search(nums, start, partition - 1, k);
    } else {
        search(nums, partition + 1, end, k - (partition - start + 1));
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
