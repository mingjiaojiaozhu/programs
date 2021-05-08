#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void longestPalindromicSubstring(char *text, char **result) {
    int length = strlen(text);
    int **aux = (int **) malloc(sizeof(int *) * length);
    for (int i = 0; i < length; ++i) {
        aux[i] = (int *) malloc(sizeof(int) * length);
        memset(aux[i], 0, sizeof(int) * length);
        aux[i][i] = 1;
    }

    int start = 0;
    int size = 1;
    for (int i = 1; i < length; ++i) {
        for (int j = 0; j < length - i; ++j) {
            int index = i + j;
            aux[j][index] = (1 == i) ? (text[j] == text[index]) : (text[j] == text[index] && aux[j + 1][index - 1]);
            if (aux[j][index] && size < i + 1) {
                start = j;
                size = i + 1;
            }
        }
    }

    *result = (char *) malloc(sizeof(char) * (length + 1));
    memset(*result, '\0', sizeof(char) * (length + 1));
    memcpy(*result, text + start, sizeof(char) * size);
}
