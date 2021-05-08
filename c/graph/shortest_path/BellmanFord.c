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

void bellmanFord(pNode *graphs, int length, int start, ArrayNode *result) {
    result->values = (int *) malloc(sizeof(int) * length);
    for (int i = 0; i < length; ++i) {
        result->values[i] = ~(1 << 31);
    }
    result->length = length;
    result->values[start] = 0;

    int index = start;
    for (int i = 0; i < length; ++i) {
        EdgeNode *edge = graphs[index]->next;
        while (edge) {
            int pivot = result->values[index] + edge->weight;
            int edgeIndex = edge->index;
            if (~(1 << 31) != result->values[index] && pivot < result->values[edgeIndex]) {
                result->values[edgeIndex] = pivot;
            }
            edge = edge->next;
        }

        ++index;
        if (index >= length) {
            index = 0;
        }
    }

    index = start;
    for (int i = 0; i < length; ++i) {
        EdgeNode *edge = graphs[index]->next;
        while (edge) {
            int pivot = result->values[index] + edge->weight;
            int edgeIndex = edge->index;
            if (~(1 << 31) != result->values[index] && pivot < result->values[edgeIndex]) {
                result->values = NULL;
                result->length = 0;
                return;
            }
            edge = edge->next;
        }

        ++index;
        if (index >= length) {
            index = 0;
        }
    }
}
