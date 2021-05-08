#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void sort(char **texts, char **aux, int start, int end, int digit);
static int getChar(char *text, int pos);

void msdRadixSort(char **texts, int length) {
    char **aux = (char **) malloc(sizeof(char *) * length);
    for (int i = 0; i < length; ++i) {
        aux[i] = "";
    }
    sort(texts, aux, 0, length - 1, 0);
}

static void sort(char **texts, char **aux, int start, int end, int digit) {
    if (start >= end) {
        return;
    }

    int maxValue = getChar(texts[start], digit);
    int minValue = getChar(texts[start], digit);
    for (int i = start + 1; i <= end; ++i) {
        int value = getChar(texts[i], digit);
        if (!~value) {
            continue;
        }

        if (maxValue < value) {
            maxValue = value;
        }
        if (!~minValue || minValue > value) {
            minValue = value;
        }
    }

    int size = maxValue - minValue + 1;
    int *buckets = (int *) malloc(sizeof(int) * (size + 2));
    memset(buckets, 0, sizeof(int) * (size + 2));
    for (int i = start; i <= end; ++i) {
        int value = getChar(texts[i], digit);
        ++buckets[!~value ? 1 : value - minValue + 2];
    }
    for (int i = 1; i < size + 2; ++i) {
        buckets[i] += buckets[i - 1];
    }

    for (int i = start; i <= end; ++i) {
        int value = getChar(texts[i], digit);
        int index = !~value ? 0 : value - minValue + 1;
        aux[buckets[index]] = texts[i];
        ++buckets[index];
    }
    for (int i = start; i <= end; ++i) {
        texts[i] = aux[i - start];
    }

    for (int i = 0; i < size; ++i) {
        sort(texts, aux, start + buckets[i], start + buckets[i + 1] - 1, digit + 1);
    }
}

static int getChar(char *text, int digit) {
    if ((int) strlen(text) <= digit) {
        return -1;
    }
    return text[digit];
}
