#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int longestCommonSubstring(char *text1, char *text2) {
    int length1 = strlen(text1);
    int length2 = strlen(text2);
    int **result = (int **) malloc(sizeof(int *) * (length1 + 1));
    for (int i = 0; i <= length1; ++i) {
        result[i] = (int *) malloc(sizeof(int) * (length2 + 1));
        memset(result[i], 0, sizeof(int) * (length2 + 1));
    }
    int maxValue = 0;
    for (int i = 1; i <= length1; ++i) {
        for (int j = 1; j <= length2; ++j) {
            result[i][j] = (text1[i - 1] == text2[j - 1]) ? result[i - 1][j - 1] + 1 : 0;
            if (maxValue < result[i][j]) {
                maxValue = result[i][j];
            }
        }
    }
    return maxValue;
}
