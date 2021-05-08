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

typedef struct {
    int *values;
    int *weights;
    int length;
} UnionFindNode;

static UnionFindNode *createUnionFind(int length);
static void addUnionFind(UnionFindNode *unionFind, int num1, int num2);
static int getUnionFind(UnionFindNode *unionFind, int num);

void boruvka(pNode *graphs, int length, ArrayNode *result) {
    EdgeListNode *edgeLists = (EdgeListNode *) malloc(sizeof(EdgeListNode));
    edgeLists->values = (ConnectedNode **) malloc(sizeof(ConnectedNode *) * 64);
    for (int i = 0; i < 64; ++i) {
        edgeLists->values[i] = NULL;
    }
    edgeLists->length = 0;
    edgeLists->capacity = 64;
    for (int i = 0; i < length; ++i) {
        EdgeNode *edge = graphs[i]->next;
        while (edge) {
            if (edgeLists->length >= edgeLists->capacity) {
                edgeLists->values = (ConnectedNode **) realloc(edgeLists->values, sizeof(ConnectedNode *) * (edgeLists->capacity + 16));
                for (int i = edgeLists->capacity; i < edgeLists->capacity + 16; ++i) {
                    edgeLists->values[i] = NULL;
                }
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

    UnionFindNode *unionFind = createUnionFind(length);
    result->values = (int *) malloc(sizeof(int) * length);
    for (int i = 0; i < length; ++i) {
        result->values[i] = -1;
    }
    result->length = length;
    while (1) {
        EdgeListNode *minEdges = (EdgeListNode *) malloc(sizeof(EdgeListNode));
        minEdges->values = (ConnectedNode **) malloc(sizeof(ConnectedNode *) * length);
        for (int i = 0; i < length; ++i) {
            minEdges->values[i] = NULL;
        }
        minEdges->length = length;
        minEdges->capacity = length;

        int flag = 0;
        for (int i = 0; i < edgeLists->length; ++i) {
            ConnectedNode *edge = edgeLists->values[i];
            int fromIndex = unionFind->values[edge->fromIndex];
            int toIndex = unionFind->values[edge->toIndex];
            if (fromIndex != toIndex && (!minEdges->values[toIndex] || edge->weight < minEdges->values[toIndex]->weight)) {
                minEdges->values[toIndex] = edge;
                flag = 1;
            }
        }

        if (!flag) {
            break;
        }

        for (int i = 0; i < minEdges->length; ++i) {
            ConnectedNode *edge = minEdges->values[i];
            if (edge) {
                int fromIndex = edge->fromIndex;
                int toIndex = edge->toIndex;
                if (getUnionFind(unionFind, fromIndex) != getUnionFind(unionFind, toIndex)) {
                    addUnionFind(unionFind, fromIndex, toIndex);
                    result->values[toIndex] = fromIndex;
                }
            }
        }
    }
}

static UnionFindNode *createUnionFind(int length) {
    UnionFindNode *node = (UnionFindNode *) malloc(sizeof(UnionFindNode));
    node->values = (int *) malloc(sizeof(int) * length);
    node->weights = (int *) malloc(sizeof(int) * length);
    for (int i = 0; i < length; ++i) {
        node->values[i] = i;
        node->weights[i] = 1;
    }
    node->length = length;
    return node;
}

static void addUnionFind(UnionFindNode *unionFind, int num1, int num2) {
    int root1 = getUnionFind(unionFind, num1);
    int root2 = getUnionFind(unionFind, num2);
    if (root1 != root2) {
        if (unionFind->weights[root1] < unionFind->weights[root2]) {
            unionFind->values[root2] = root1;
            unionFind->weights[root1] += unionFind->weights[root2];
        } else {
            unionFind->values[root1] = root2;
            unionFind->weights[root2] += unionFind->weights[root1];
        }
    }
}

static int getUnionFind(UnionFindNode *unionFind, int num) {
    int root = num;
    while (root != unionFind->values[root]) {
        root = unionFind->values[root];
    }

    while (num != root) {
        int aux = unionFind->values[num];
        unionFind->values[num] = root;
        num = aux;
    }
    return root;
}
