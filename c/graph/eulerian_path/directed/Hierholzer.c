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
    int capacity;
} ArrayNode;

static void search(pNode *graphs, int length, int start, int **visited, ArrayNode *result);
static int getStart(pNode *graphs, int length);
static void reverse(ArrayNode *values);

void hierholzer(pNode *graphs, int length, ArrayNode *result) {
    int start = getStart(graphs, length);
    if (!~start) {
        result->values = NULL;
        result->length = 0;
        return;
    }

    int **visited = (int **) malloc(sizeof(int *) * length);
    for (int i = 0; i < length; ++i) {
        visited[i] = (int *) malloc(sizeof(int) * length);
        memset(visited[i], 0, sizeof(int) * length);
    }

    result->values = (int *) malloc(sizeof(int) * 64);
    memset(result->values, 0, sizeof(int) * 64);
    result->length = 0;
    result->capacity = 64;
    search(graphs, length, start, visited, result);
    reverse(result);
}

static void search(pNode *graphs, int length, int start, int **visited, ArrayNode *result) {
    EdgeNode *edge = graphs[start]->next;
    while (edge) {
        int edgeIndex = edge->index;
        if (!visited[start][edgeIndex]) {
            visited[start][edgeIndex] = 1;
            search(graphs, length, edgeIndex, visited, result);
        }
        edge = edge->next;
    }

    if (result->length >= result->capacity) {
        result->values = (int *) realloc(result->values, sizeof(int) * (result->capacity + 16));
        memset(result->values + result->capacity, 0, sizeof(int) * 16);
        result->capacity += 16;
    }
    result->values[result->length] = start;
    ++result->length;
}

static int getStart(pNode *graphs, int length) {
    int *inDegrees = (int *) malloc(sizeof(int) * length);
    memset(inDegrees, 0, sizeof(int) * length);
    int *outDegrees = (int *) malloc(sizeof(int) * length);
    memset(outDegrees, 0, sizeof(int) * length);
    for (int i = 0; i < length; ++i) {
        EdgeNode *edge = graphs[i]->next;
        while (edge) {
            ++inDegrees[edge->index];
            ++outDegrees[i];
            edge = edge->next;
        }
    }

    int start = 0;
    int inCount = 0;
    int outCount = 0;
    for (int i = length - 1; i >= 0; --i) {
        if (abs(inDegrees[i] - outDegrees[i]) > 1) {
            return -1;
        }

        if (1 == outDegrees[i] - inDegrees[i]) {
            start = i;
            ++inCount;
        } else if (1 == inDegrees[i] - outDegrees[i]) {
            ++outCount;
        }
        if (inCount > 1 || outCount > 1) {
            break;
        }
    }
    return ((!inCount && !outCount) || (1 == inCount && 1 == outCount)) ? start : -1;
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
