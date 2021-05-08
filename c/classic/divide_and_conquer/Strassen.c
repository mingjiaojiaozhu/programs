#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int **values;
    int length;
} ArrayNode;

static int **multiply(int **matrix1, int **matrix2, int length);
static int **add(int **matrix1, int **matrix2, int length);
static int **subtract(int **matrix1, int **matrix2, int length);
static void split(int **matrix, int **matrixTopLeft, int **matrixTopRight, int **matrixBottomLeft, int **matrixBottomRight, int length, int halfSize);
static int **merge(int **matrixTopLeft, int **matrixTopRight, int **matrixBottomLeft, int **matrixBottomRight, int length, int halfSize);
static int **createArrays(int length, int value);

void strassen(int **matrix1, int **matrix2, int length, ArrayNode *result) {
    result->values = multiply(matrix1, matrix2, length);
    result->length = length;
}

static int **multiply(int **matrix1, int **matrix2, int length) {
    if (1 == length) {
        return createArrays(length, matrix1[0][0] * matrix2[0][0]);
    }

    int halfSize = (length & (length - 1)) ? (length >> 1) + 1 : length >> 1;
    int **matrix1TopLeft = createArrays(halfSize, 0);
    int **matrix1TopRight = createArrays(halfSize, 0);
    int **matrix1BottomLeft = createArrays(halfSize, 0);
    int **matrix1BottomRight = createArrays(halfSize, 0);
    split(matrix1, matrix1TopLeft, matrix1TopRight, matrix1BottomLeft, matrix1BottomRight, length, halfSize);
    int **matrix2TopLeft = createArrays(halfSize, 0);
    int **matrix2TopRight = createArrays(halfSize, 0);
    int **matrix2BottomLeft = createArrays(halfSize, 0);
    int **matrix2BottomRight = createArrays(halfSize, 0);
    split(matrix2, matrix2TopLeft, matrix2TopRight, matrix2BottomLeft, matrix2BottomRight, length, halfSize);

    int **aux1 = multiply(add(matrix1TopLeft, matrix1BottomRight, halfSize), add(matrix2TopLeft, matrix2BottomRight, halfSize), halfSize);
    int **aux2 = multiply(add(matrix1BottomLeft, matrix1BottomRight, halfSize), matrix2TopLeft, halfSize);
    int **aux3 = multiply(matrix1TopLeft, subtract(matrix2TopRight, matrix2BottomRight, halfSize), halfSize);
    int **aux4 = multiply(matrix1BottomRight, subtract(matrix2BottomLeft, matrix2TopLeft, halfSize), halfSize);
    int **aux5 = multiply(add(matrix1TopLeft, matrix1TopRight, halfSize), matrix2BottomRight, halfSize);
    int **aux6 = multiply(subtract(matrix1BottomLeft, matrix1TopLeft, halfSize), add(matrix2TopLeft, matrix2TopRight, halfSize), halfSize);
    int **aux7 = multiply(subtract(matrix1TopRight, matrix1BottomRight, halfSize), add(matrix2BottomLeft, matrix2BottomRight, halfSize), halfSize);

    int **resultTopLeft = add(subtract(add(aux1, aux4, halfSize), aux5, halfSize), aux7, halfSize);
    int **resultTopRight = add(aux3, aux5, halfSize);
    int **resultBottomLeft = add(aux2, aux4, halfSize);
    int **resultBottomRight = add(add(subtract(aux1, aux2, halfSize), aux3, halfSize), aux6, halfSize);
    return merge(resultTopLeft, resultTopRight, resultBottomLeft, resultBottomRight, length, halfSize);
}

static int **add(int **matrix1, int **matrix2, int length) {
    int **result = createArrays(length, 0);
    for (int i = 0; i < length; ++i) {
        memcpy(result[i], matrix1[i], sizeof(int) * length);
        for (int j = 0; j < length; ++j) {
            result[i][j] += matrix2[i][j];
        }
    }
    return result;
}

static int **subtract(int **matrix1, int **matrix2, int length) {
    int **result = createArrays(length, 0);
    for (int i = 0; i < length; ++i) {
        memcpy(result[i], matrix1[i], sizeof(int) * length);
        for (int j = 0; j < length; ++j) {
            result[i][j] -= matrix2[i][j];
        }
    }
    return result;
}

static void split(int **matrix, int **matrixTopLeft, int **matrixTopRight, int **matrixBottomLeft, int **matrixBottomRight, int length, int halfSize) {
    for (int i = 0; i < halfSize - 1; ++i) {
        memcpy(matrixTopLeft[i], matrix[i], sizeof(int) * halfSize);
        memcpy(matrixTopRight[i], matrix[i] + halfSize, sizeof(int) * (length - halfSize));
        memcpy(matrixBottomLeft[i], matrix[halfSize + i], sizeof(int) * halfSize);
        memcpy(matrixBottomRight[i], matrix[halfSize + i] + halfSize, sizeof(int) * (length - halfSize));
        if (length & (length - 1)) {
            matrixTopRight[i][halfSize - 1] = 0;
            matrixBottomRight[i][halfSize - 1] = 0;
        }
    }

    memcpy(matrixTopLeft[halfSize - 1], matrix[halfSize - 1], sizeof(int) * halfSize);
    memcpy(matrixTopRight[halfSize - 1], matrix[halfSize - 1] + halfSize, sizeof(int) * (length - halfSize));
    if (length & (length - 1)) {
        matrixTopRight[halfSize - 1][halfSize - 1] = 0;
        memset(matrixBottomLeft[halfSize - 1], 0, sizeof(int) * halfSize);
        memset(matrixBottomRight[halfSize - 1], 0, sizeof(int) * halfSize);
    } else {
        memcpy(matrixBottomLeft[halfSize - 1], matrix[length - 1], sizeof(int) * halfSize);
        memcpy(matrixBottomRight[halfSize - 1], matrix[length - 1] + halfSize, sizeof(int) * (length - halfSize));
    }
}

static int **merge(int **matrixTopLeft, int **matrixTopRight, int **matrixBottomLeft, int **matrixBottomRight, int length, int halfSize) {
    int **result = createArrays(length, 0);
    for (int i = 0; i < halfSize - 1; ++i) {
        memcpy(result[i], matrixTopLeft[i], sizeof(int) * halfSize);
        memcpy(result[i] + halfSize, matrixTopRight[i], sizeof(int) * (length - halfSize));
        memcpy(result[halfSize + i], matrixBottomLeft[i], sizeof(int) * halfSize);
        memcpy(result[halfSize + i] + halfSize, matrixBottomRight[i], sizeof(int) * (length - halfSize));
    }
    memcpy(result[halfSize - 1], matrixTopLeft[halfSize - 1], sizeof(int) * halfSize);
    memcpy(result[halfSize - 1] + halfSize, matrixTopRight[halfSize - 1], sizeof(int) * (length - halfSize));
    if (!(length & (length - 1))) {
        memcpy(result[length - 1], matrixBottomLeft[halfSize - 1], sizeof(int) * halfSize);
        memcpy(result[length - 1] + halfSize, matrixBottomRight[halfSize - 1], sizeof(int) * (length - halfSize));
    }
    return result;
}

static int **createArrays(int length, int value) {
    int **values = (int **) malloc(sizeof(int *) * length);
    for (int i = 0; i < length; ++i) {
        values[i] = (int *) malloc(sizeof(int) * length);
        for (int j = 0; j < length; ++j) {
            values[i][j] = value;
        }
    }
    return values;
}
