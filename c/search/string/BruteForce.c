#include <stdio.h>
#include <string.h>

int bruteForce(char *text, char *pattern) {
    int length = strlen(text);
    int patternLength = strlen(pattern);

    int index = 0;
    int patternIndex = 0;
    while (index < length) {
        if (text[index] != pattern[patternIndex]) {
            index += 1 - patternIndex;
            patternIndex = 0;
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
