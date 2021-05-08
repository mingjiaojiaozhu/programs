#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int *getNext(char *text, int length);

int knuthMorrisPratt(char *text, char *pattern) {
    int length = strlen(text);
    int patternLength = strlen(pattern);
    int *next = getNext(pattern, patternLength);

    int index = 0;
    int patternIndex = 0;
    while (index < length) {
        if (patternIndex > 0 && text[index] != pattern[patternIndex]) {
            ++index;
            patternIndex = next[patternIndex - 1];
            continue;
        }

        if (patternIndex == patternLength - 1) {
            return index - patternIndex;
        }
        ++index;
        ++patternIndex;
    }
    return -1;
}

static int *getNext(char *text, int length) {
    int *next = (int *) malloc(sizeof(int) * length);
    memset(next, 0, sizeof(int) * length);

    int fast = 1;
    int slow = 0;
    while (fast < length) {
        if (slow && text[fast] != text[slow]) {
            slow = next[slow - 1];
            continue;
        }

        if (text[fast] == text[slow]) {
            ++slow;
        }
        next[fast] = slow;
        ++fast;
    }
    return next;
}
