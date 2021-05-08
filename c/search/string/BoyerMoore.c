#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int *getNextBadChar(char *text, int length, int nextSize, int minValue);
static int *getNextGoodSuffix(char *text, int length);
static int max(int i, int j);

int boyerMoore(char *text, char *pattern) {
    int length = strlen(text);
    int patternLength = strlen(pattern);

    int maxValue = text[0];
    int minValue = text[0];
    for (char *p = text + 1; '\0' != *p; ++p) {
        if (maxValue < *p) {
            maxValue = *p;
        }
        if (minValue > *p) {
            minValue = *p;
        }
    }
    int *nextBadChar = getNextBadChar(pattern, patternLength, maxValue - minValue + 1, minValue);
    int *nextGoodSuffix = getNextGoodSuffix(pattern, patternLength);

    int index = 0;
    while (index <= length - patternLength) {
        int patternIndex = patternLength - 1;
        while (text[index + patternIndex] == pattern[patternIndex]) {
            --patternIndex;
            if (patternIndex < 0) {
                return index;
            }
        }
        index += max(patternIndex - nextBadChar[text[index + patternIndex] - minValue], nextGoodSuffix[patternIndex]);
    }
    return -1;
}

static int *getNextBadChar(char *text, int length, int nextSize, int minValue) {
    int *next = (int *) malloc(sizeof(int) * nextSize);
    memset(next, 0, sizeof(int) * nextSize);
    for (int i = 0; i < length; ++i) {
        int index = text[i] - minValue;
        if (index >= 0 && index < nextSize) {
            next[index] = i;
        }
    }
    return next;
}

static int *getNextGoodSuffix(char *text, int length) {
    int *aux = (int *) malloc(sizeof(int) * length);
    memset(aux, 0, sizeof(int) * length);
    aux[length - 1] = length;

    int start = 0;
    int end = length - 1;
    for (int i = length - 2; i >= 0; --i) {
        if (i > end && aux[i + length - 1 - start] < i - end) {
            aux[i] = aux[i + length - 1 - start];
            continue;
        }

        start = i;
        if (i < end) {
            end = i;
        }
        while (end >= 0 && text[end] == text[end + length - 1 - start]) {
            --end;
            aux[i] = start - end;
        }
    }

    int *next = (int *) malloc(sizeof(int) * length);
    for (int i = 0; i < length; ++i) {
        next[i] = length;
    }
    for (int i = length - 1; i >= 0; --i) {
        if (aux[i] != i + 1) {
            continue;
        }

        for (int j = 0; j < length - i; ++j) {
            if (next[j] == length) {
                next[j] = length - i - 1;
            }
        }
    }

    for (int i = 0; i < length - 1; ++i) {
        next[length - 1 - aux[i]] = length - i - 1;
    }
    return next;
}

static int max(int i, int j) {
    int aux = ~((i > j) ? 1 : 0) + 1;
    return (i & aux) | (j & ~aux);
}
