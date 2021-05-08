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

typedef struct queue {
    int value;
    struct queue *prev;
    struct queue *next;
} ListNode;

typedef struct {
    ListNode *head;
    ListNode *tail;
} QueueNode;

static int *topologicalSort(pNode *graphs, int length, StackNode *stack);
static int *reverseTopologicalSort(pNode *graphs, int length, int *vertexEnd, StackNode *stack);
static StackNode *createStack();
static void pushStack(StackNode *stack, int value);
static int popStack(StackNode *stack);
static QueueNode *createQueue();
static void enqueue(QueueNode *queue, int value);
static int dequeue(QueueNode *queue);

void criticalPath(pNode *graphs, int length, ArrayNode *result) {
    StackNode *stack = createStack();
    int *vertexEnd = topologicalSort(graphs, length, stack);
    if (!vertexEnd) {
        result->values = NULL;
        result->length = 0;
        return;
    }
    int *vertexLatest = reverseTopologicalSort(graphs, length, vertexEnd, stack);

    result->values = (int *) malloc(sizeof(int) * length);
    memset(result->values, 0, sizeof(int) * length);
    result->length = 0;
    for (int i = 0; i < length; ++i) {
        if (vertexEnd[i] == vertexLatest[i]) {
            result->values[result->length] = i;
            ++result->length;
        }
    }
}

static int *topologicalSort(pNode *graphs, int length, StackNode *stack) {
    int *inDegrees = (int *) malloc(sizeof(int) * length);
    memset(inDegrees, 0, sizeof(int) * length);
    for (int i = 0; i < length; ++i) {
        EdgeNode *edge = graphs[i]->next;
        while (edge) {
            ++inDegrees[edge->index];
            edge = edge->next;
        }
    }

    QueueNode *queue = createQueue();
    for (int i = 0; i < length; ++i) {
        if (!inDegrees[i]) {
            enqueue(queue, i);
        }
    }

    int *vertexEnd = (int *) malloc(sizeof(int) * length);
    memset(vertexEnd, 0, sizeof(int) * length);
    int count = 0;
    while (queue->head->next != queue->tail) {
        int index = dequeue(queue);
        pushStack(stack, index);
        ++count;

        EdgeNode *edge = graphs[index]->next;
        int pivot = vertexEnd[index];
        while (edge) {
            int edgeIndex = edge->index;
            int edgeWeight = edge->weight;
            --inDegrees[edgeIndex];
            if (!inDegrees[edgeIndex]) {
                enqueue(queue, edgeIndex);
                if (vertexEnd[edgeIndex] < pivot + edgeWeight) {
                    vertexEnd[edgeIndex] = pivot + edgeWeight;
                }
            }
            edge = edge->next;
        }
    }
    return (count == length) ? vertexEnd : NULL;
}

static int *reverseTopologicalSort(pNode *graphs, int length, int *vertexEnd, StackNode *stack) {
    int maxValue = vertexEnd[popStack(stack)];
    int *vertexLatest = (int *) malloc(sizeof(int) * length);
    for (int i = 0; i < length; ++i) {
        vertexLatest[i] = maxValue;
    }
    while (stack->next) {
        int index = popStack(stack);
        EdgeNode *edge = graphs[index]->next;
        while (edge) {
            int edgeIndex = edge->index;
            int edgeWeight = edge->weight;
            if (vertexLatest[index] > vertexLatest[edgeIndex] - edgeWeight) {
                vertexLatest[index] = vertexLatest[edgeIndex] - edgeWeight;
            }
            edge = edge->next;
        }
    }
    return vertexLatest;
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

static QueueNode *createQueue() {
    QueueNode *queue = (QueueNode *) malloc(sizeof(QueueNode));
    queue->head = (ListNode *) malloc(sizeof(ListNode));
    queue->tail = (ListNode *) malloc(sizeof(ListNode));
    queue->head->value = 0;
    queue->tail->value = 0;
    queue->head->prev = NULL;
    queue->tail->prev = queue->head;
    queue->head->next = queue->tail;
    queue->tail->next = NULL;
    return queue;
}

static void enqueue(QueueNode *queue, int value) {
    ListNode *node = (ListNode *) malloc(sizeof(ListNode));
    node->value = value;
    node->prev = queue->tail->prev;
    node->next = queue->tail;
    queue->tail->prev->next = node;
    queue->tail->prev = node;
}

static int dequeue(QueueNode *queue) {
    ListNode *node = queue->head->next;
    node->next->prev = queue->head;
    queue->head->next = node->next;
    return node->value;
}
