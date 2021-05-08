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

static int search(pNode *graphs, int length, int start, int end, int index, int minValue, int **weights, int *gap, int *degrees);
static int min(int i, int j);

int sap(pNode *graphs, int length, int start, int end) {
    int **weights = (int **) malloc(sizeof(int *) * length);
    for (int i = 0; i < length; ++i) {
        weights[i] = (int *) malloc(sizeof(int) * length);
        memset(weights[i], 0, sizeof(int) * length);
        EdgeNode *edge = graphs[i]->next;
        while (edge) {
            weights[i][edge->index] = edge->weight;
            edge = edge->next;
        }
    }

    int *gap = (int *) malloc(sizeof(int) * (length + 1));
    memset(gap, 0, sizeof(int) * (length + 1));
    gap[0] = length;
    int *degrees = (int *) malloc(sizeof(int) * length);
    memset(degrees, 0, sizeof(int) * length);
    int result = 0;
    while (degrees[start] != length) {
        result += search(graphs, length, start, end, start, ~(1 << 31), weights, gap, degrees);
    }
    return result;
}

static int search(pNode *graphs, int length, int start, int end, int index, int minValue, int **weights, int *gap, int *degrees) {
    if (index == end) {
        return minValue;
    }

    EdgeNode *edge = graphs[index]->next;
    int pivot = minValue;
    int border = length - 1;
    while (edge) {
        int edgeIndex = edge->index;
        if (weights[index][edgeIndex]) {
            if (degrees[index] == degrees[edgeIndex] + 1) {
                int value = search(graphs, length, start, end, edgeIndex, min(pivot, weights[index][edgeIndex]), weights, gap, degrees);
                weights[index][edgeIndex] -= value;
                weights[edgeIndex][index] += value;
                pivot -= value;
                if (degrees[start] == length || !pivot) {
                    return minValue - pivot;
                }
            }
            if (border > degrees[edgeIndex]) {
                border = degrees[edgeIndex];
            }
        }
        edge = edge->next;
    }

    --gap[degrees[index]];
    if (!~gap[degrees[index]]) {
        degrees[start] = length;
    } else {
        degrees[index] = border + 1;
        ++gap[degrees[index]];
    }
    return minValue - pivot;
}

static int min(int i, int j) {
    int aux = ~((i > j) ? 1 : 0) + 1;
    return (i & ~aux) | (j & aux);
}
