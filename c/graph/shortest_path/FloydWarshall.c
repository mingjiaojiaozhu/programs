#include <stdio.h>
#include <stdlib.h>

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

typedef struct {
    ArrayNode *values;
    int length;
} DoublyArrayNode;

void floydWarshall(pNode *graphs, int length, DoublyArrayNode *result) {
    result->values = (ArrayNode *) malloc(sizeof(ArrayNode) * length);
    for (int i = 0; i < length; ++i) {
        result->values[i].values = (int *) malloc(sizeof(int) * length);
        for (int j = 0; j < length; ++j) {
            result->values[i].values[j] = ~(1 << 31);
        }
        result->values[i].length = length;

        EdgeNode *edge = graphs[i]->next;
        while (edge) {
            result->values[i].values[edge->index] = edge->weight;
            edge = edge->next;
        }
        result->values[i].values[i] = 0;
    }
    result->length = length;

    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < length; ++j) {
            for (int k = 0; k < length; ++k) {
                if (~(1 << 31) == result->values[j].values[i] || ~(1 << 31) == result->values[i].values[k]) {
                    continue;
                }

                int pivot = result->values[j].values[i] + result->values[i].values[k];
                if (pivot < result->values[j].values[k]) {
                    result->values[j].values[k] = pivot;
                }
            }
        }
    }
}
