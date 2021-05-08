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
    int index;
    int weight;
} HeapNode;

typedef struct {
    HeapNode *values;
    int length;
} QueueNode;

static QueueNode *createQueue(int length);
static void enqueue(QueueNode *queue, int index, int weight);
static HeapNode dequeue(QueueNode *queue);

void dijkstra(pNode *graphs, int length, int start, ArrayNode *result) {
    int *visited = (int *) malloc(sizeof(int) * length);
    memset(visited, 0, sizeof(int) * length);
    QueueNode *queue = createQueue(length);
    enqueue(queue, start, 0);

    result->values = (int *) malloc(sizeof(int) * length);
    for (int i = 0; i < length; ++i) {
        result->values[i] = ~(1 << 31);
    }
    result->length = length;
    while (queue->length) {
        HeapNode heap = dequeue(queue);
        int index = heap.index;
        int weight = heap.weight;
        if (visited[index]) {
            continue;
        }

        result->values[index] = weight;
        visited[index] = 1;

        EdgeNode *edge = graphs[index]->next;
        while (edge) {
            int edgeIndex = edge->index;
            int edgeWeight = weight + edge->weight;
            if (!visited[edgeIndex]) {
                enqueue(queue, edgeIndex, edgeWeight);
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

static void enqueue(QueueNode *queue, int index, int weight) {
    int child = queue->length;
    while (child > 0) {
        int parent = (child - 1) >> 1;
        if (queue->values[parent].weight <= weight) {
            break;
        }
        queue->values[child] = queue->values[parent];
        child = parent;
    }
    queue->values[child].index = index;
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
