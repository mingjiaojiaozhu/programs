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
    ArrayNode *values;
    int length;
} DoublyArrayNode;

typedef struct stack {
    int value;
    struct stack *next;
} StackNode;

static void search(pNode *graphs, int length, int start, int *visited, StackNode *stack);
static void reverseSearch(pNode *graphs, int length, int start, int *visited, ArrayNode *aux);
static StackNode *createStack();
static void pushStack(StackNode *stack, int value);
static int popStack(StackNode *stack);

void kosarajuSharir(pNode *graphs, int length, DoublyArrayNode *result) {
    int *visited = (int *) malloc(sizeof(int) * length);
    memset(visited, 0, sizeof(int) * length);
    StackNode *stack = createStack();
    search(graphs, length, 0, visited, stack);

    pNode *inverseGraphs = (pNode *) malloc(sizeof(pNode) * length);
    for (int i = 0; i < length; ++i) {
        inverseGraphs[i] = (pNode) malloc(sizeof(VertexNode));
        inverseGraphs[i]->value = graphs[i]->value;
        inverseGraphs[i]->next = NULL;
    }
    for (int i = length - 1; i >= 0; --i) {
        EdgeNode *edge = graphs[i]->next;
        while (edge) {
            int edgeIndex = edge->index;
            EdgeNode *edgeNode = (EdgeNode *) malloc(sizeof(EdgeNode));
            edgeNode->index = i;
            edgeNode->weight = edge->weight;
            edgeNode->next = inverseGraphs[edgeIndex]->next;
            inverseGraphs[edgeIndex]->next = edgeNode;
            edge = edge->next;
        }
    }

    memset(visited, 0, sizeof(int) * length);
    result->values = (ArrayNode *) malloc(sizeof(ArrayNode) * length);
    for (int i = 0; i < length; ++i) {
        result->values[i].values = NULL;
    }
    result->length = 0;

    ArrayNode *aux = (ArrayNode *) malloc(sizeof(ArrayNode));
    aux->values = (int *) malloc(sizeof(int) * length);
    memset(aux->values, 0, sizeof(int) * length);
    aux->length = 0;
    while (stack->next) {
        int index = popStack(stack);
        if (!visited[index]) {
            reverseSearch(inverseGraphs, length, index, visited, aux);
            result->values[result->length].values = (int *) malloc(sizeof(int) * aux->length);
            memcpy(result->values[result->length].values, aux->values, sizeof(int) * aux->length);
            result->values[result->length].length = aux->length;
            ++result->length;

            memset(aux->values, 0, sizeof(int) * aux->length);
            aux->length = 0;
        }
    }
}

static void search(pNode *graphs, int length, int start, int *visited, StackNode *stack) {
    visited[start] = 1;
    EdgeNode *edge = graphs[start]->next;
    while (edge) {
        int edgeIndex = edge->index;
        if (!visited[edgeIndex]) {
            search(graphs, length, edgeIndex, visited, stack);
        }
        edge = edge->next;
    }
    pushStack(stack, start);
}

static void reverseSearch(pNode *graphs, int length, int start, int *visited, ArrayNode *aux) {
    visited[start] = 1;
    aux->values[aux->length] = start;
    ++aux->length;

    EdgeNode *edge = graphs[start]->next;
    while (edge) {
        int edgeIndex = edge->index;
        if (!visited[edgeIndex]) {
            reverseSearch(graphs, length, edgeIndex, visited, aux);
        }
        edge = edge->next;
    }
}

static StackNode *createStack() {
    StackNode *stack = (StackNode *) malloc(sizeof(StackNode));
    stack->value = 0;
    stack->next = NULL;
    return stack;
}

static void pushStack(StackNode *stack, int value) {
    StackNode *node = (StackNode *) malloc(sizeof(StackNode));
    node->value = value;
    node->next = stack->next;
    stack->next = node;
}

static int popStack(StackNode *stack) {
    StackNode *node = stack->next;
    stack->next = node->next;
    return node->value;
}
