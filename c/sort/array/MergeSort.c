#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void sort(int *nums, int *aux, int start, int end);
static void merge(int *nums, int *aux, int start, int middle, int end);

void mergeSort(int *nums, int length) {
    int *aux = (int *) malloc(sizeof(int) * length);
    memcpy(aux, nums, sizeof(int) * length);
    sort(nums, aux, 0, length - 1);
}

static void sort(int *nums, int *aux, int start, int end) {
    if (start >= end) {
        return;
    }

    int middle = start + ((end - start) >> 1);
    sort(aux, nums, start, middle);
    sort(aux, nums, middle + 1, end);

    if (aux[middle] > aux[middle + 1]) {
        merge(nums, aux, start, middle, end);
    } else {
        memcpy(nums + start, aux + start, sizeof(int) * (end - start + 1));
    }
}

static void merge(int *nums, int *aux, int start, int middle, int end) {
    int index = start;
    int left = start;
    int right = middle + 1;
    while (left <= middle && right <= end) {
        if (aux[left] > aux[right]) {
            nums[index] = aux[right];
            ++right;
        } else {
            nums[index] = aux[left];
            ++left;
        }
        ++index;
    }

    if (left <= middle) {
        memcpy(nums + index, aux + left, sizeof(int) * (middle - left + 1));
    }
    if (right <= end) {
        memcpy(nums + index, aux + right, sizeof(int) * (end - right + 1));
    }
}
