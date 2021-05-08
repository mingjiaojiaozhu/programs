#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void lsdRadixSort(char **texts, int length) {
    char **aux = (char **) malloc(sizeof(char *) * length);
    for (int i = 0; i < length; ++i) {
        aux[i] = "";
    }
    for (int i = strlen(texts[0]) - 1; i >= 0; --i) {
        int maxValue = texts[0][i];
        int minValue = texts[0][i];
        for (int j = 1; j < length; ++j) {
            int value = texts[j][i];
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
        int *buckets = (int *) malloc(sizeof(int) * size);
        memset(buckets, 0, sizeof(int) * size);
        for (int j = 0; j < length; ++j) {
            ++buckets[texts[j][i] - minValue];
        }
        for (int j = 1; j < size; ++j) {
            buckets[j] += buckets[j - 1];
        }

        for (int j = length - 1; j >= 0; --j) {
            int index = texts[j][i] - minValue;
            aux[buckets[index] - 1] = texts[j];
            --buckets[index];
        }
        for (int j = 0; j < length; ++j) {
            texts[j] = aux[j];
        }
    }
}
