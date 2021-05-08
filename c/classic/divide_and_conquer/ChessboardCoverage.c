#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
    int *values;
    int length;
} ArrayNode;

typedef struct {
    ArrayNode *values;
    int length;
} DoublyArrayNode;

static int cover(int size, int row, int col, int startRow, int startCol, int index, DoublyArrayNode *result);

void chessboardCoverage(int k, int *square, DoublyArrayNode *result) {
    int size = (int) pow((double) 2, k);
    result->values = (ArrayNode *) malloc(sizeof(ArrayNode) * size);
    for (int i = 0; i < size; ++i) {
        result->values[i].values = (int *) malloc(sizeof(int) * size);
        memset(result->values[i].values, 0, sizeof(int) * size);
        result->values[i].length = size;
    }
    result->length = size;
    cover(size, square[0], square[1], 0, 0, 1, result);
}

static int cover(int size, int row, int col, int startRow, int startCol, int index, DoublyArrayNode *result) {
    size >>= 1;
    if (!size) {
        return index - 1;
    }

    int value = index;
    ++index;
    if (row < startRow + size && col < startCol + size) {
        index = cover(size, row, col, startRow, startCol, index, result);
    } else {
        result->values[startRow + size - 1].values[startCol + size - 1] = value;
        index = cover(size, startRow + size - 1, startCol + size - 1, startRow, startCol, index, result);
    }

    ++index;
    if (row < startRow + size && col >= startCol + size) {
        index = cover(size, row, col, startRow, startCol + size, index, result);
    } else {
        result->values[startRow + size - 1].values[startCol + size] = value;
        index = cover(size, startRow + size - 1, startCol + size, startRow, startCol + size, index, result);
    }

    ++index;
    if (row >= startRow + size && col < startCol + size) {
        index = cover(size, row, col, startRow + size, startCol, index, result);
    } else {
        result->values[startRow + size].values[startCol + size - 1] = value;
        index = cover(size, startRow + size, startCol + size - 1, startRow + size, startCol, index, result);
    }

    ++index;
    if (row >= startRow + size && col >= startCol + size) {
        index = cover(size, row, col, startRow + size, startCol + size, index, result);
    } else {
        result->values[startRow + size].values[startCol + size] = value;
        index = cover(size, startRow + size, startCol + size, startRow + size, startCol + size, index, result);
    }
    return index;
}
