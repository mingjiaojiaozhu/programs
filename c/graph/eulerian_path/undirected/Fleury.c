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

typedef struct stack {
    int value;
    struct stack *next;
} StackNode;

static void search(pNode *graphs, int length, int start, StackNode *stack, int **visited);
static int getStart(pNode *graphs, int length);
static void reverse(ArrayNode *values);
static StackNode *createStack();
static void pushStack(StackNode *stack, int value);
static int popStack(StackNode *stack);

void fleury(pNode *graphs, int length, ArrayNode *result) {
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
    StackNode *stack = createStack();
    pushStack(stack, start);

    result->values = (int *) malloc(sizeof(int) * 64);
    memset(result->values, 0, sizeof(int) * 64);
    result->length = 0;
    result->capacity = 64;
    while (stack->next) {
        int index = popStack(stack);
        EdgeNode *edge = graphs[index]->next;
        int flag = 0;
        while (edge) {
            int edgeIndex = edge->index;
            if (!visited[index][edgeIndex]) {
                flag = 1;
                break;
            }
            edge = edge->next;
        }
        if (!flag) {
            if (result->length >= result->capacity) {
                result->values = (int *) realloc(result->values, sizeof(int) * (result->capacity + 16));
                memset(result->values + result->capacity, 0, sizeof(int) * 16);
                result->capacity += 16;
            }
            result->values[result->length] = index;
            ++result->length;
        } else {
            search(graphs, length, index, stack, visited);
        }
    }
    reverse(result);
}

static void search(pNode *graphs, int length, int start, StackNode *stack, int **visited) {
    pushStack(stack, start);
    EdgeNode *edge = graphs[start]->next;
    while (edge) {
        int edgeIndex = edge->index;
        if (!visited[start][edgeIndex]) {
            visited[start][edgeIndex] = 1;
            visited[edgeIndex][start] = 1;
            search(graphs, length, edgeIndex, stack, visited);
            break;
        }
        edge = edge->next;
    }
}

static int getStart(pNode *graphs, int length) {
    int start = 0;
    int oddCount = 0;
    for (int i = length - 1; i >= 0; --i) {
        int count = 0;
        EdgeNode *edge = graphs[i]->next;
        while (edge) {
            ++count;
            edge = edge->next;
        }
        if (count & 1) {
            start = i;
            ++oddCount;
            if (oddCount > 2) {
                break;
            }
        }
    }
    return (!oddCount || 2 == oddCount) ? start : -1;
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
