#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **values;
    int length;
} ArrayNode;

typedef struct {
    ArrayNode *values;
    int length;
    int capacity;
} DoublyArrayNode;

static void search(int num, int row, int col, int left, int right, int *aux, DoublyArrayNode *result);
static int getBits(int value);

void eightQueens(int num, DoublyArrayNode *result) {
    result->values = (ArrayNode *) malloc(sizeof(ArrayNode) * 64);
    for (int i = 0; i < 64; ++i) {
        result->values[i].values = NULL;
        result->values[i].length = 0;
    }
    result->length = 0;
    result->capacity = 64;
    int *aux = (int *) malloc(sizeof(int) * num);
    for (int i = 0; i < num; ++i) {
        aux[i] = -1;
    }
    search(num, 0, 0, 0, 0, aux, result);
}

static void search(int num, int row, int col, int left, int right, int *aux, DoublyArrayNode *result) {
    if (row == num) {
        if (result->length >= result->capacity) {
            result->values = (ArrayNode *) realloc(result->values, sizeof(ArrayNode) * (result->capacity + 16));
            for (int i = result->capacity; i < result->capacity + 16; ++i) {
                result->values[i].values = NULL;
                result->values[i].length = 0;
            }
            result->capacity += 16;
        }
        char **lines = (char **) malloc(sizeof(char *) * num);
        for (int i = 0; i < num; ++i) {
            char *line = (char *) malloc(sizeof(char) * (num + 1));
            memset(line, '0', sizeof(char) * num);
            line[aux[i]] = '1';
            line[num] = '\0';
            lines[i] = line;
        }
        result->values[result->length].values = lines;
        result->values[result->length].length = num;
        ++result->length;
        return;
    }

    int mask = ((1 << num) - 1) & (~(col | left | right));
    while (mask) {
        int pos = mask & (~mask + 1);
        mask &= (mask - 1);
        aux[row] = getBits(pos - 1);
        search(num, row + 1, col | pos, (left | pos) << 1, (right | pos) >> 1, aux, result);
        aux[row] = -1;
    }
}

static int getBits(int value) {
    int result = 0;
    while (value) {
        ++result;
        value &= value - 1;
    }
    return result;
}
