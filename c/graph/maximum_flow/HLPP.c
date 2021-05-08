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
    int index;
    int degree;
} HeapNode;

typedef struct {
    HeapNode *values;
    int length;
} QueueNode;

static void search(pNode *graphs, int length, int start, int end, int **weights, int *gap, int *degrees, QueueNode *queue, int *result);
static int min(int i, int j);
static QueueNode *createQueue(int length);
static void enqueue(QueueNode *queue, int index, int weight);
static HeapNode dequeue(QueueNode *queue);

int hlpp(pNode *graphs, int length, int start, int end) {
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

    int *gap = (int *) malloc(sizeof(int) * length);
    memset(gap, 0, sizeof(int) * length);
    int *degrees = (int *) malloc(sizeof(int) * length);
    memset(degrees, 0, sizeof(int) * length);
    degrees[start] = length;
    QueueNode *queue = createQueue(length);
    int *result = (int *) malloc(sizeof(int) * length);
    memset(result, 0, sizeof(int) * length);
    result[start] = ~(1 << 31);

    EdgeNode *edge = graphs[start]->next;
    while (edge) {
        int edgeIndex = edge->index;
        int value = min(result[start], weights[start][edgeIndex]);
        weights[start][edgeIndex] -= value;
        weights[edgeIndex][start] += value;
        result[start] -= value;
        result[edgeIndex] += value;
        if (value && edgeIndex != end) {
            enqueue(queue, edgeIndex, degrees[edgeIndex]);
        }
        edge = edge->next;
    }

    while (queue->length) {
        HeapNode heap = dequeue(queue);
        int index = heap.index;
        if (result[index]) {
            search(graphs, length, index, end, weights, gap, degrees, queue, result);
        }
    }
    return result[end];
}

static void search(pNode *graphs, int length, int start, int end, int **weights, int *gap, int *degrees, QueueNode *queue, int *result) {
    EdgeNode *edge = graphs[start]->next;
    while (edge) {
        int edgeIndex = edge->index;
        if (degrees[start] == degrees[edgeIndex] + 1) {
            int value = min(result[start], weights[start][edgeIndex]);
            weights[start][edgeIndex] -= value;
            weights[edgeIndex][start] += value;
            result[start] -= value;
            result[edgeIndex] += value;
            if (value && edgeIndex != end) {
                enqueue(queue, edgeIndex, degrees[edgeIndex]);
            }
        }
        edge = edge->next;
    }

    if (start != end && result[start]) {
        --gap[degrees[start]];
        if (!~gap[degrees[start]]) {
            for (int i = 0;i < length; ++i) {
                if (i != end && degrees[i] > degrees[start] && degrees[i] < length) {
                    degrees[i]= length;
                }
            }
        }
        ++degrees[start];
        if (degrees[start] < length) {
            ++gap[degrees[start]];
            enqueue(queue, start, degrees[start]);
        }
    }
}

static int min(int i, int j) {
    int aux = ~((i > j) ? 1 : 0) + 1;
    return (i & ~aux) | (j & aux);
}

static QueueNode *createQueue(int length) {
    QueueNode *queue = (QueueNode *) malloc(sizeof(QueueNode));
    queue->values = (HeapNode *) malloc(sizeof(HeapNode) * length);
    queue->length = 0;
    return queue;
}

static void enqueue(QueueNode *queue, int index, int degree) {
    int child = queue->length;
    while (child > 0) {
        int parent = (child - 1) >> 1;
        if (queue->values[parent].degree >= degree) {
            break;
        }
        queue->values[child] = queue->values[parent];
        child = parent;
    }
    queue->values[child].index = index;
    queue->values[child].degree = degree;
    ++queue->length;
}

static HeapNode dequeue(QueueNode *queue) {
    --queue->length;
    HeapNode value = queue->values[0];
    HeapNode pivot = queue->values[queue->length];
    int parent = 0;
    while (1) {
        int child = (parent << 1) + 1;
        if (child >= queue->length) {
            break;
        }

        if (child < queue->length - 1 && queue->values[child].degree < queue->values[child + 1].degree) {
            ++child;
        }
        if (queue->values[child].degree <= pivot.degree) {
            break;
        }
        queue->values[parent] = queue->values[child];
        parent = child;
    }
    queue->values[parent] = pivot;
    return value;
}
