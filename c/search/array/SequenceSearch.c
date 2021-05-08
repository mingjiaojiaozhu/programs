#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sequenceSearch(int *nums, int length, int target) {
    int *aux = (int *) malloc(sizeof(int) * (length + 1));
    memcpy(aux, nums, sizeof(int) * length);
    aux[length] = target;

    int index = 0;
    while (target != aux[index]) {
        ++index;
    }
    return (index < length) ? index : -1;
}
