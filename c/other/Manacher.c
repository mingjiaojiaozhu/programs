#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int min(int i, int j);

void manacher(char *text, char **result) {
    int length = strlen(text);
    char *aux = (char *) malloc(sizeof(char) * ((length << 1) + 2));
    memset(aux, '\0', sizeof(char) * ((length << 1) + 2));
    aux[0] = '|';
    for (int i = 0; i < length; ++i) {
        aux[(i << 1) + 1] = text[i];
        aux[(i << 1) + 2] = '|';
    }

    int border = 0;
    int middle = 0;
    int center = 0;
    int maxLength = 0;
    int *buckets = (int *) malloc(sizeof(int) * ((length << 1) + 1));
    memset(buckets, 0, sizeof(int) * ((length << 1) + 1));
    for (int i = 0; i <= length << 1; ++i) {
        if (i < border) {
            int index = (middle << 1) - i;
            buckets[i] = min(buckets[index], border - i);
            if (i + buckets[index] < border) {
                continue;
            }
        }

        int left = i - buckets[i] - 1;
        int right = i + buckets[i] + 1;
        while (left >= 0 && right <= length << 1) {
            if (aux[left] != aux[right]) {
                break;
            }
            ++buckets[i];

            --left;
            ++right;
        }

        border = buckets[i] + i;
        middle = i;
        if (maxLength < buckets[i]) {
            maxLength = buckets[i];
            center = i;
        }
    }

    *result = (char *) malloc(sizeof(char) * (length + 1));
    memset(*result, '\0', sizeof(char) * (length + 1));
    int index = 0;
    for (int i = center - maxLength; i <= center + maxLength; ++i) {
        char value = aux[i];
        if ('|' != value) {
            (*result)[index] = value;
            ++index;
        }
    }
}

static int min(int i, int j) {
    int aux = ~((i > j) ? 1 : 0) + 1;
    return (i & ~aux) | (j & aux);
}
