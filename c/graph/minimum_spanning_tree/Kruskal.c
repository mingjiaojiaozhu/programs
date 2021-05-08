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

typedef struct {
    int fromIndex;
    int toIndex;
    int weight;
} ConnectedNode;

typedef struct {
    ConnectedNode **values;
    int length;
    int capacity;
} EdgeListNode;

static int getRoot(int *roots, int index);
static int cmp(const void *p, const void *q);

void kruskal(pNode *graphs, int length, ArrayNode *result) {
    EdgeListNode *edgeLists = (EdgeListNode *) malloc(sizeof(EdgeListNode));
    edgeLists->values = (ConnectedNode **) malloc(sizeof(ConnectedNode *) * 64);
    edgeLists->length = 0;
    edgeLists->capacity = 64;
    for (int i = 0; i < length; ++i) {
        EdgeNode *edge = graphs[i]->next;
        while (edge) {
            if (edgeLists->length >= edgeLists->capacity) {
                edgeLists->values = (ConnectedNode **) realloc(edgeLists->values, sizeof(ConnectedNode *) * (edgeLists->capacity + 16));
                edgeLists->capacity += 16;
            }
            edgeLists->values[edgeLists->length] = (ConnectedNode *) malloc(sizeof(ConnectedNode));
            edgeLists->values[edgeLists->length]->fromIndex = i;
            edgeLists->values[edgeLists->length]->toIndex = edge->index;
            edgeLists->values[edgeLists->length]->weight = edge->weight;
            ++edgeLists->length;

            edge = edge->next;
        }
    }

    qsort(edgeLists->values, edgeLists->length, sizeof(ConnectedNode *), cmp);

    int *roots = (int *) malloc(sizeof(int) * length);
    for (int i = 0; i < length; ++i) {
        roots[i] = -1;
    }
    int *visited = (int *) malloc(sizeof(int) * length);
    memset(visited, 0, sizeof(int) * length);

    result->values = (int *) malloc(sizeof(int) * length);
    for (int i = 0; i < length; ++i) {
        result->values[i] = -1;
    }
    result->length = length;
    for (int i = 0; i < edgeLists->length; ++i) {
        ConnectedNode *edge = edgeLists->values[i];
        int fromIndex = edge->fromIndex;
        int toIndex = edge->toIndex;
        if (!visited[toIndex] && getRoot(roots, fromIndex) != getRoot(roots, toIndex)) {
            result->values[toIndex] = fromIndex;
            roots[fromIndex] = toIndex;
            visited[toIndex] = 1;
        }
    }
}

static int getRoot(int *roots, int index) {
    while (~roots[index]) {
        index = roots[index];
    }
    return index;
}

static int cmp(const void *p, const void *q) {
    return (*((ConnectedNode **) p))->weight - (*((ConnectedNode **) q))->weight;
}
