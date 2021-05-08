#include <stdio.h>
#include <string.h>

static void sort(char **texts, int start, int end, int digit);
static int getChar(char *text, int digit);
static void swap(char **p, char **q);

void quickSort(char **texts, int length) {
    sort(texts, 0, length - 1, 0);
}

static void sort(char **texts, int start, int end, int digit) {
    if (start >= end) {
        return;
    }

    int pivot = getChar(texts[start], digit);
    int left = start;
    int right = end;
    int index = start;
    while (index <= right) {
        int value = getChar(texts[index], digit);
        if (pivot == value) {
            ++index;
            continue;
        }

        if (value < pivot) {
            swap(&texts[left], &texts[index]);

            ++index;
            ++left;
        } else {
            swap(&texts[index], &texts[right]);
            --right;
        }
    }

    sort(texts, start, left - 1, digit);
    if (~pivot) {
        sort(texts, left, right, digit + 1);
    }
    sort(texts, right + 1, end, digit);
}

static int getChar(char *text, int digit) {
    if ((int) strlen(text) <= digit) {
        return -1;
    }
    return text[digit];
}

static void swap(char **p, char **q) {
    char *temp = *p;
    *p = *q;
    *q = temp;
}
