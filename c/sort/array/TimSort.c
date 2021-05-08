#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *values;
    int length;
} ArrayNode;

static int getRunLength(int *nums, int start, int end);
static void insertSort(int *nums, int start, int end, int index);
static void mergeRuns(int *nums, int *aux, ArrayNode *runBase, ArrayNode *runSize);
static void merge(int *nums, int *aux, int runIndex, ArrayNode *runBase, ArrayNode *runSize);
static int gallopLeft(int *nums, int base, int size, int pivot);
static int gallopRight(int *nums, int base, int size, int pivot);
static void reverse(int *start, int *end);
static int min(int i, int j);

void timSort(int *nums, int length) {
    if (length < 16) {
        int runLength = getRunLength(nums, 0, length);
        insertSort(nums, 0, length, runLength);
        return;
    }

    int *aux = (int *) malloc(sizeof(int) * length);
    memcpy(aux, nums, sizeof(int) * length);
    ArrayNode *runBase = (ArrayNode *) malloc(sizeof(ArrayNode));
    runBase->values = (int *) malloc(sizeof(int) * length);
    memset(runBase->values, 0, sizeof(int) * length);
    runBase->length = 0;
    ArrayNode *runSize = (ArrayNode *) malloc(sizeof(ArrayNode));
    runSize->values = (int *) malloc(sizeof(int) * length);
    memset(runSize->values, 0, sizeof(int) * length);
    runSize->length = 0;

    int start = 0;
    int end = length;
    while (end > 0) {
        int runLength = getRunLength(nums, start, length);
        if (runLength < 16) {
            int size = min(end, 16);
            insertSort(nums, start, start + size, start + runLength);
            runLength = size;
        }

        runBase->values[runBase->length] = start;
        ++runBase->length;
        runSize->values[runSize->length] = runLength;
        ++runSize->length;
        mergeRuns(nums, aux, runBase, runSize);

        start += runLength;
        end -= runLength;
    }

    while (runBase->length > 1) {
        merge(nums, aux, runBase->length - 2, runBase, runSize);
    }
}

static int getRunLength(int *nums, int start, int end) {
    if (start + 1 == end) {
        return 1;
    }

    int index = start + 1;
    if (nums[start] > nums[index]) {
        while (index < end - 1 && nums[index] > nums[index + 1]) {
            ++index;
        }
        reverse(nums + start, nums + index);
    } else {
        while (index < end - 1 && nums[index] <= nums[index + 1]) {
            ++index;
        }
    }
    return index - start + 1;
}

static void insertSort(int *nums, int start, int end, int index) {
    for (int i = index; i < end; ++i) {
        int pivot = nums[i];
        if (pivot >= nums[i - 1]) {
            continue;
        }

        int left = start;
        int right = i - 1;
        while (left <= right) {
            int middle = left + ((right - left) >> 1);
            if (pivot < nums[middle]) {
                right = middle - 1;
            } else {
                left = middle + 1;
            }
        }

        for (int j = i - 1; j >= left; --j) {
            nums[j + 1] = nums[j];
        }
        nums[left] = pivot;
    }
}

static void mergeRuns(int *nums, int *aux, ArrayNode *runBase, ArrayNode *runSize) {
    while (runBase->length > 1) {
        int index = runBase->length - 2;
        if (index > 0 && runSize->values[index - 1] <= runSize->values[index] + runSize->values[index + 1]) {
            if (runSize->values[index - 1] < runSize->values[index + 1]) {
                --index;
            }
            merge(nums, aux, index, runBase, runSize);
        } else if (runSize->values[index] <= runSize->values[index + 1]) {
            merge(nums, aux, index, runBase, runSize);
        } else {
            return;
        }
    }
}

static void merge(int *nums, int *aux, int runIndex, ArrayNode *runBase, ArrayNode *runSize) {
    int base1 = runBase->values[runIndex];
    int size1 = runSize->values[runIndex];
    int base2 = runBase->values[runIndex + 1];
    int size2 = runSize->values[runIndex + 1];
    runSize->values[runIndex] = size1 + size2;
    if (runIndex == runSize->length - 3) {
        runBase[runIndex + 1] = runBase[runIndex + 2];
        runSize[runIndex + 1] = runSize[runIndex + 2];
    }
    --runBase->length;
    --runSize->length;

    int start = gallopLeft(nums, base1, size1, nums[base2]);
    if (start >= base1 + size1) {
        return;
    }
    int end = gallopRight(nums, base2, size2, nums[base1 + size1 - 1]);
    if (end < base2) {
        return;
    }
    memcpy(aux + start, nums + start, sizeof(int) * (end - start + 1));

    int index = start;
    int left1 = start;
    int right1 = base1 + size1 - 1;
    int left2 = base2;
    int right2 = end;
    while (left1 <= right1 && left2 <= right2) {
        if (aux[left1] > aux[left2]) {
            nums[index] = aux[left2];
            ++left2;
        } else {
            nums[index] = aux[left1];
            ++left1;
        }
        ++index;
    }

    if (left1 <= right1) {
        memcpy(nums + index, aux + left1, sizeof(int) * (right1 - left1 + 1));
    }
    if (left2 <= right2) {
        memcpy(nums + index, aux + left2, sizeof(int) * (right2 - left2 + 1));
    }
}

static int gallopLeft(int *nums, int base, int size, int pivot) {
    int start = base;
    int end = base + size - 1;
    while (start <= end) {
        int middle = start + ((end - start) >> 1);
        if (pivot <= nums[middle]) {
            end = middle - 1;
        } else {
            start = middle + 1;
        }
    }
    return end + 1;
}

static int gallopRight(int *nums, int base, int size, int pivot) {
    int start = base;
    int end = base + size - 1;
    while (start <= end) {
        int middle = start + ((end - start) >> 1);
        if (pivot >= nums[middle]) {
            start = middle + 1;
        } else {
            end = middle - 1;
        }
    }
    return start - 1;
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

static int min(int i, int j) {
    int aux = ~((i > j) ? 1 : 0) + 1;
    return (i & ~aux) | (j & aux);
}
