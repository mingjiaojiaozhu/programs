#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *values;
    int length;
} ArrayNode;

static int search(int **graphs, int length, int start, ArrayNode *result, int **visited, int **weights);

void kuhnMunkres(int **graphs, int length, ArrayNode *result) {
    int **weights = (int **) malloc(sizeof(int *) * 3);
    weights[0] = (int *) malloc(sizeof(int) * length);
    memset(weights[0], 0, sizeof(int) * length);
    weights[1] = (int *) malloc(sizeof(int) * length);
    for (int i = 0; i < length; ++i) {
        int maxValue = graphs[i][0];
        for (int j = 1; j < length; ++j) {
            if (maxValue < graphs[i][j]) {
                maxValue = graphs[i][j];
            }
        }
        weights[1][i] = maxValue;
    }
    weights[2] = (int *) malloc(sizeof(int) * length);
    for (int i = 0; i < length; ++i) {
        weights[2][i] = ~(1 << 31);
    }

    int **visited = (int **) malloc(sizeof(int *) * 2);
    for (int i = 0; i < 2; ++i) {
        visited[i] = (int *) malloc(sizeof(int) * length);
        memset(visited[i], 0, sizeof(int) * length);
    }

    result->values = (int *) malloc(sizeof(int) * length);
    for (int i = 0; i < length; ++i) {
        result->values[i] = -1;
    }
    result->length = length;
    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < length; ++j) {
            weights[2][j] = ~(1 << 31);
        }
        while (1) {
            memset(visited[0], 0, sizeof(int) * (length));
            memset(visited[1], 0, sizeof(int) * (length));
            if (search(graphs, length, i, result, visited, weights)) {
                break;
            }

            int weight = ~(1 << 31);
            for (int j = 0; j < length; ++j) {
                if (!visited[0][j] && weight > weights[2][j]) {
                    weight = weights[2][j];
                }
            }

            for (int j = 0; j < length; ++j) {
                if (visited[1][j]) {
                    weights[1][j] -= weight;
                }

                if (visited[0][j]) {
                    weights[0][j] += weight;
                } else {
                    weights[2][j] -= weight;
                }
            }
        }
    }
}

static int search(int **graphs, int length, int start, ArrayNode *result, int **visited, int **weights) {
    visited[1][start] = 1;
    for (int i = 0; i < length; ++i) {
        if (visited[0][i]) {
            continue;
        }

        int weight = weights[1][start] + weights[0][i] - graphs[start][i];
        if (!weight) {
            visited[0][i] = 1;
            if (!~result->values[i] || search(graphs, length, result->values[i], result, visited, weights)) {
                result->values[i] = start;
                return 1;
            }
        } else {
            if (weights[2][i] > weight) {
                weights[2][i] = weight;
            }
        }
    }
    return 0;
}
