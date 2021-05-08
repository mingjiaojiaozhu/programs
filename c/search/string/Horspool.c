#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int *getNext(char *text, int length, int nextSize, int minValue);

int horspool(char *text, char *pattern) {
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
    int *next = getNext(pattern, patternLength, maxValue - minValue + 1, minValue);

    int index = 0;
    while (index <= length - patternLength) {
        int patternIndex = patternLength - 1;
        while (text[index + patternIndex] == pattern[patternIndex]) {
            --patternIndex;
            if (patternIndex < 0) {
                return index;
            }
        }
        index += next[text[index + patternLength - 1] - minValue];
    }
    return -1;
}

static int *getNext(char *text, int length, int nextSize, int minValue) {
    int *next = (int *) malloc(sizeof(int) * nextSize);
    for (int i = 0; i < nextSize; ++i) {
        next[i] = length;
    }
    for (int i = 0; i < length - 1; ++i) {
        int index = text[i] - minValue;
        if (index >= 0 && index < nextSize) {
            next[index] = length - i - 1;
        }
    }
    return next;
}
