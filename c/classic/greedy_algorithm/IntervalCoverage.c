#include <stdio.h>
#include <stdlib.h>

static int cmp(const void *p, const void *q);

int intervalCoverage(int **values, int length, int *target) {
    qsort(values, length, sizeof(int *), cmp);

    int start = target[0];
    int end = target[1];
    int index = 0;
    int result = 0;
    while (start < end) {
        int border = start;
        while (index < length && start >= values[index][0]) {
            if (border < values[index][1]) {
                border = values[index][1];
            }
            ++index;
        }

        if (border == start) {
            return -1;
        }

        ++result;
        start = border;
    }
    return result;
}

static int cmp(const void *p, const void *q) {
    return (*((int **) p))[0] - (*((int **) q))[0];
}
