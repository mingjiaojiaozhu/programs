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
} HeapNode;

typedef struct {
    HeapNode *values;
    int length;
} QueueNode;

static QueueNode *createQueue(int length);
static void enqueue(QueueNode *queue, int fromIndex, int toIndex, int weight);
static HeapNode dequeue(QueueNode *queue);

void prim(pNode *graphs, int length, int start, ArrayNode *result) {
    int *visited = (int *) malloc(sizeof(int) * length);
    memset(visited, 0, sizeof(int) * length);
    QueueNode *queue = createQueue(length);
    enqueue(queue, -1, start, 0);

    result->values = (int *) malloc(sizeof(int) * length);
    for (int i = 0; i < length; ++i) {
        result->values[i] = -1;
    }
    result->length = length;
    while (queue->length) {
        HeapNode heap = dequeue(queue);
        int fromIndex = heap.fromIndex;
        int toIndex = heap.toIndex;
        if (visited[toIndex]) {
            continue;
        }

        result->values[toIndex] = fromIndex;
        visited[toIndex] = 1;

        EdgeNode *edge = graphs[toIndex]->next;
        while (edge) {
            int edgeIndex = edge->index;
            int edgeWeight = edge->weight;
            if (!visited[edgeIndex]) {
                enqueue(queue, toIndex, edgeIndex, edgeWeight);
            }
            edge = edge->next;
        }
    }
}

static QueueNode *createQueue(int length) {
    QueueNode *queue = (QueueNode *) malloc(sizeof(QueueNode));
    queue->values = (HeapNode *) malloc(sizeof(HeapNode) * length);
    queue->length = 0;
    return queue;
}

static void enqueue(QueueNode *queue, int fromIndex, int toIndex, int weight) {
    int child = queue->length;
    while (child > 0) {
        int parent = (child - 1) >> 1;
        if (queue->values[parent].weight <= weight) {
            break;
        }
        queue->values[child] = queue->values[parent];
        child = parent;
    }
    queue->values[child].fromIndex = fromIndex;
    queue->values[child].toIndex = toIndex;
    queue->values[child].weight = weight;
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

        if (child < queue->length - 1 && queue->values[child].weight > queue->values[child + 1].weight) {
            ++child;
        }
        if (queue->values[child].weight >= pivot.weight) {
            break;
        }
        queue->values[parent] = queue->values[child];
        parent = child;
    }
    queue->values[parent] = pivot;
    return value;
}
