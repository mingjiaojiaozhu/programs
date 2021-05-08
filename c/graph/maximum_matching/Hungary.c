#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *values;
    int length;
} ArrayNode;

static int search(int **graphs, int length, int start, ArrayNode *result, int *visited);

void hungary(int **graphs, int length, ArrayNode *result) {
    int *visited = (int *) malloc(sizeof(int) * length);
    memset(visited, 0, sizeof(int) * length);
    result->values = (int *) malloc(sizeof(int) * length);
    for (int i = 0; i < length; ++i) {
        result->values[i] = -1;
    }
    result->length = length;
    for (int i = 0; i < length; ++i) {
        memset(visited, 0, sizeof(int) * length);
        if (!search(graphs, length, i, result, visited)) {
            result->values = NULL;
            result->length = 0;
            return;
        }
    }
}

static int search(int **graphs, int length, int start, ArrayNode *result, int *visited) {
    for (int i = 0; i < length; ++i) {
        if (graphs[i][start] && !visited[i]) {
            visited[i] = 1;
            if (!~result->values[i] || search(graphs, length, result->values[i], result, visited)) {
                result->values[i] = start;
                return 1;
            }
        }
    }
    return 0;
}
