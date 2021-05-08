#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    int index;
    int weight;
    struct node *next;
} EdgeNode;

typedef struct {
    int value;
    EdgeNode *next;
} VertexNode;

typedef VertexNode *pNode;

typedef struct {
    int *values;
    int length;
} ArrayNode;

static int search(pNode *graphs, int start, ArrayNode *result, int **visited);
static void reverse(ArrayNode *values);

void topologicalSort(pNode *graphs, int length, ArrayNode *result) {
    int **visited = (int **) malloc(sizeof(int *) * 2);
    for (int i = 0; i < 2; ++i) {
        visited[i] = (int *) malloc(sizeof(int) * length);
        memset(visited[i], 0, sizeof(int) * length);
    }

    result->values = (int *) malloc(sizeof(int) * length);
    memset(result->values, 0, sizeof(int) * length);
    result->length = 0;
    for (int i = 0; i < length; ++i) {
        if (!visited[0][i] && !search(graphs, i, result, visited)) {
            result->values = NULL;
            result->length = 0;
            return;
        }
    }
    reverse(result);
}

static int search(pNode *graphs, int start, ArrayNode *result, int **visited) {
    visited[1][start] = 1;
    EdgeNode *edge = graphs[start]->next;
    while (edge) {
        int edgeIndex = edge->index;
        if (visited[1][edgeIndex] || (!visited[0][edgeIndex] && !search(graphs, edgeIndex, result, visited))) {
            return 0;
        }
        edge = edge->next;
    }

    visited[0][start] = 1;
    visited[1][start] = 0;
    result->values[result->length] = start;
    ++result->length;
    return 1;
}

static void reverse(ArrayNode *values) {
    int start = 0;
    int end = values->length - 1;
    while (start < end) {
        values->values[start] ^= values->values[end];
        values->values[end] ^= values->values[start];
        values->values[start] ^= values->values[end];

        ++start;
        --end;
    }
}
