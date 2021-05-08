#include <stdio.h>
#include <stdlib.h>

static int cmp(const void *p, const void *q);

int activitySelection(int **values, int length) {
    qsort(values, length, sizeof(int *), cmp);

    int end = values[0][1];
    int result = 1;
    for (int i = 1; i < length; ++i) {
        if (end <= values[i][0]) {
            end = values[i][1];
            ++result;
        }
    }
    return result;
}

static int cmp(const void *p, const void *q) {
    return (*((int **) p))[1] - (*((int **) q))[1];
}
