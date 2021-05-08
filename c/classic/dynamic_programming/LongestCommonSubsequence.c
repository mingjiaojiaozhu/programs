#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int max(int i, int j);

int longestCommonSubsequence(char *text1, char *text2) {
    int length1 = strlen(text1);
    int length2 = strlen(text2);
    int **result = (int **) malloc(sizeof(int *) * (length1 + 1));
    for (int i = 0; i <= length1; ++i) {
        result[i] = (int *) malloc(sizeof(int) * (length2 + 1));
        memset(result[i], 0, sizeof(int) * (length2 + 1));
    }
    for (int i = 1; i <= length1; ++i) {
        for (int j = 1; j <= length2; ++j) {
            result[i][j] = (text1[i - 1] == text2[j - 1]) ? result[i - 1][j - 1] + 1 : max(result[i - 1][j], result[i][j - 1]);
        }
    }
    return result[length1][length2];
}

static int max(int i, int j) {
    int aux = ~((i > j) ? 1 : 0) + 1;
    return (i & aux) | (j & ~aux);
}
