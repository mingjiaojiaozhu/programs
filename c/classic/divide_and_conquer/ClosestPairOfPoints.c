#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *values;
    int length;
} ArrayNode;

typedef struct {
    ArrayNode *values;
    int length;
} DoublyArrayNode;

static int match(int **points, int length, DoublyArrayNode *result);
static int getBorder(int **points, int length, int index, int target);
static int getDistance(int *point1, int *point2);
static int cmpOfX(const void *p, const void *q);
static int cmpOfY(const void *p, const void *q);
static int min(int i, int j);

void closestPairOfPoints(int **points, int length, DoublyArrayNode *result) {
    result->values = (ArrayNode *) malloc(sizeof(ArrayNode) * 2);
    for (int i = 0; i < 2; ++i) {
        result->values[i].length = 2;
    }
    result->length = 2;
    match(points, length, result);
}

static int match(int **points, int length, DoublyArrayNode *result) {
    if (length < 2) {
        return ~(1 << 31);
    }
    if (2 == length) {
        result->values[0].values = points[0];
        result->values[1].values = points[1];
        return getDistance(points[0], points[1]);
    }

    qsort(points, length, sizeof(int *), cmpOfX);

    int halfSize = length >> 1;
    int **left = (int **) malloc(sizeof(int *) * halfSize);
    memcpy(left, points, sizeof(int *) * halfSize);
    DoublyArrayNode *aux1 = (DoublyArrayNode *) malloc(sizeof(DoublyArrayNode));
    aux1->values = (ArrayNode *) malloc(sizeof(ArrayNode) * 2);
    int distance1 = match(left, halfSize, aux1);

    int **right = (int **) malloc(sizeof(int *) * (length - halfSize));
    memcpy(right, points + halfSize, sizeof(int *) * (length - halfSize));
    DoublyArrayNode *aux2 = (DoublyArrayNode *) malloc(sizeof(DoublyArrayNode));
    aux2->values = (ArrayNode *) malloc(sizeof(ArrayNode) * 2);
    int distance2 = match(right, length - halfSize, aux2);

    int minDistance = min(distance1, distance2);
    if (distance1 < distance2) {
        result->values[0].values = aux1->values[0].values;
        result->values[1].values = aux1->values[1].values;
    } else {
        result->values[0].values = aux2->values[0].values;
        result->values[1].values = aux2->values[1].values;
    }

    int border1 = getBorder(left, halfSize, 0, points[halfSize][0] - minDistance);
    int border2 = getBorder(right, length - halfSize, 0, points[halfSize][0] + minDistance);
    if (border1 == halfSize || !border2) {
        return minDistance;
    }

    int **aux = (int **) malloc(sizeof(int *) * border2);
    memcpy(aux, right, sizeof(int *) * border2);
    qsort(aux, border2, sizeof(int *), cmpOfY);

    for (int i = border1; i < halfSize; ++i) {
        int start = getBorder(aux, border2, 1, left[i][1] - minDistance);
        int end = getBorder(aux, border2, 1, left[i][1] + minDistance);
        for (int j = start; j < end; ++j) {
            int distance = getDistance(left[i], right[j]);
            if (minDistance > distance) {
                result->values[0].values = left[i];
                result->values[1].values = right[j];
                minDistance = distance;
            }
        }
    }
    return minDistance;
}

static int getBorder(int **points, int length, int index, int target) {
    int start = 0;
    int end = length - 1;
    while (start <= end) {
        int middle = start + ((end - start) >> 1);
        if (target < points[middle][index]) {
            end = middle - 1;
        } else {
            start = middle + 1;
        }
    }
    return start;
}

static int getDistance(int *point1, int *point2) {
    return abs(point2[0] - point1[0]) + abs(point2[1] - point1[1]);
}

static int cmpOfX(const void *p, const void *q) {
    return (*((int **) p))[0] - (*((int **) q))[0];
}

static int cmpOfY(const void *p, const void *q) {
    return (*((int **) p))[1] - (*((int **) q))[1];
}

static int min(int i, int j) {
    int aux = ~((i > j) ? 1 : 0) + 1;
    return (i & ~aux) | (j & aux);
}
