#include <stdio.h>
#include <string.h>

static int getHashCode(char *text, int length);

int rabinKarp(char *text, char *pattern) {
    int length = strlen(text);
    int patternLength = strlen(pattern);

    int code = getHashCode(text, patternLength);
    int patternCode = getHashCode(pattern, patternLength);
    for (int i = 0; i <= length - patternLength; ++i) {
        if (code == patternCode) {
            int index = i;
            int patternIndex = 0;
            while (index < length) {
                if (text[index] != pattern[patternIndex]) {
                    break;
                }

                if (patternIndex == patternLength - 1) {
                    return index - patternIndex;
                }
                ++index;
                ++patternIndex;
            }
        }

        if (i < length - patternLength) {
            code += text[i + patternLength] - text[i];
        }
    }
    return -1;
}

static int getHashCode(char *text, int length) {
    int code = 0;
    for (int i = 0; i < length; ++i) {
        code += text[i] - 'a';
    }
    return code;
}
