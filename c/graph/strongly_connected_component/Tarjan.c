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

static int search(pNode *graphs, int length, int start, int *parent, StackNode *stack, DoublyArrayNode *result, ArrayNode *aux, int count);
static StackNode *createStack();
static void pushStack(StackNode *stack, int value);
static int popStack(StackNode *stack);

void tarjan(pNode *graphs, int length, DoublyArrayNode *result) {
    int *parent = (int *) malloc(sizeof(int) * length);
    for (int i = 0; i < length; ++i) {
        parent[i] = -1;
    }
    StackNode *stack = createStack();

    result->values = (ArrayNode *) malloc(sizeof(ArrayNode) * length);
    for (int i = 0; i < length; ++i) {
        result->values[i].values = NULL;
    }
    result->length = 0;

    ArrayNode *aux = (ArrayNode *) malloc(sizeof(ArrayNode));
    aux->values = (int *) malloc(sizeof(int) * length);
    memset(aux->values, 0, sizeof(int) * length);
    aux->length = 0;
    for (int i = 0; i < length; ++i) {
        if (!~parent[i]) {
            search(graphs, length, i, parent, stack, result, aux, 0);
        }
    }
}

static int search(pNode *graphs, int length, int start, int *parent, StackNode *stack, DoublyArrayNode *result, ArrayNode *aux, int count) {
    parent[start] = count;
    int minValue = count;
    pushStack(stack, start);

    EdgeNode *edge = graphs[start]->next;
    while (edge) {
        int edgeIndex = edge->index;
        if (!~parent[edgeIndex]) {
            count = search(graphs, length, edgeIndex, parent, stack, result, aux, count + 1);
        }
        edge = edge->next;

        if (minValue > parent[edgeIndex]) {
            minValue = parent[edgeIndex];
        }
    }

    if (parent[start] > minValue) {
        parent[start] = minValue;
        return count;
    }

    int index = popStack(stack);
    while (index != start) {
        aux->values[aux->length] = index;
        ++aux->length;
        parent[index] = ~(1 << 31);
        index = popStack(stack);
    }
    aux->values[aux->length] = start;
    ++aux->length;
    parent[start] = ~(1 << 31);

    result->values[result->length].values = (int *) malloc(sizeof(int) * aux->length);
    memcpy(result->values[result->length].values, aux->values, sizeof(int) * aux->length);
    result->values[result->length].length = aux->length;
    ++result->length;

    memset(aux->values, 0, sizeof(int) * aux->length);
    aux->length = 0;
    return count;
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
