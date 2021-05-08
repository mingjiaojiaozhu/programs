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

typedef struct stack {
    int value;
    struct stack *next;
} StackNode;

static StackNode *createStack();
static void pushStack(StackNode *stack, int value);
static int popStack(StackNode *stack);

void dfs(pNode *graphs, int length, int start, ArrayNode *result) {
    int *visited = (int *) malloc(sizeof(int) * length);
    memset(visited, 0, sizeof(int) * length);
    StackNode *stack = createStack();
    pushStack(stack, start);

    result->values = (int *) malloc(sizeof(int) * length);
    memset(result->values, 0, sizeof(int) * length);
    result->length = 0;
    while (stack->next) {
        int index = popStack(stack);
        if (visited[index]) {
            continue;
        }

        result->values[result->length] = index;
        ++result->length;
        visited[index] = 1;

        EdgeNode *edge = graphs[index]->next;
        while (edge) {
            int edgeIndex = edge->index;
            if (!visited[edgeIndex]) {
                pushStack(stack, edgeIndex);
            }
            edge = edge->next;
        }
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
