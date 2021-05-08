#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int (*values)[2];
    int length;
    int capacity;
} ArrayNode;

static int search(int **nums, int *lines, int *columns, int **blocks, ArrayNode *spaces, int index, int flag);
static void fill(int *lines, int *columns, int **blocks, int row, int col, int digit);
static int getBits(int value);

void sudoku(int **nums, int length) {
    int *lines = (int *) malloc(sizeof(int) * length);
    memset(lines, 0, sizeof(int) * length);
    int *columns = (int *) malloc(sizeof(int) * length);
    memset(columns, 0, sizeof(int) * length);
    int **blocks = (int **) malloc(sizeof(int *) * (length / 3));
    for (int i = 0; i < length / 3; ++i) {
        blocks[i] = (int *) malloc(sizeof(int) * (length / 3));
        memset(blocks[i], 0, sizeof(int) * (length / 3));
    }
    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < length; ++j) {
            if (nums[i][j]) {
                fill(lines, columns, blocks, i, j, nums[i][j] - 1);
            }
        }
    }

    while (1) {
        int flag = 0;
        for (int i = 0; i < length; ++i) {
            for (int j = 0; j < length; ++j) {
                if (!nums[i][j]) {
                    int mask = ~(lines[i] | columns[j] | blocks[i / 3][j / 3]) & 0x1ff;
                    if (!(mask & (mask - 1))) {
                        int digit = getBits(mask - 1);
                        fill(lines, columns, blocks, i, j, digit);
                        nums[i][j] = digit + 1;
                        flag = 1;
                    }
                }
            }
        }
        if (!flag) {
            break;
        }
    }

    ArrayNode *spaces = (ArrayNode *) malloc(sizeof(ArrayNode));
    spaces->values = (int (*)[2]) malloc(sizeof(int[2]) * 64);
    spaces->length = 0;
    spaces->capacity = 64;
    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < length; ++j) {
            if (!nums[i][j]) {
                if (spaces->length >= spaces->capacity) {
                    spaces->values = (int (*)[2]) realloc(spaces->values, sizeof(int[2]) * (spaces->capacity + 16));
                    spaces->capacity += 16;
                }
                spaces->values[spaces->length][0] = i;
                spaces->values[spaces->length][1] = j;
                ++spaces->length;
            }
        }
    }
    search(nums, lines, columns, blocks, spaces, 0, 0);
}

static int search(int **nums, int *lines, int *columns, int **blocks, ArrayNode *spaces, int index, int flag) {
    if (index == spaces->length) {
        return 1;
    }

    int row = spaces->values[index][0];
    int col = spaces->values[index][1];
    int mask = ~(lines[row] | columns[col] | blocks[row / 3][col / 3]) & 0x1ff;
    while (mask && !flag) {
        int pos = mask & (~mask + 1);
        mask &= (mask - 1);
        int digit = getBits(pos - 1);
        fill(lines, columns, blocks, row, col, digit);
        nums[row][col] = digit + 1;
        flag = search(nums, lines, columns, blocks, spaces, index + 1, flag);
        fill(lines, columns, blocks, row, col, digit);
    }
    return flag;
}

static void fill(int *lines, int *columns, int **blocks, int row, int col, int digit) {
    lines[row] ^= (1 << digit);
    columns[col] ^= (1 << digit);
    blocks[row / 3][col / 3] ^= (1 << digit);
}

static int getBits(int value) {
    int result = 0;
    while (value) {
        ++result;
        value &= value - 1;
    }
    return result;
}
