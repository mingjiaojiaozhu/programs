#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    int index;
    int weight;
    int price;
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
    int price;
} HeapNode;

typedef struct {
    HeapNode *values;
    int length;
} QueueNode;

static int search(pNode *graphs, int length, int start, int end, int **weights, int *parent, int *maxFlow, int *minCost, int *offset);
static int min(int i, int j);
static QueueNode *createQueue(int length);
static void enqueue(QueueNode *queue, int index, int weight);
static HeapNode dequeue(QueueNode *queue);

void dijkstra(pNode *graphs, int length, int start, int end, ArrayNode *result) {
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

    int *parent = (int *) malloc(sizeof(int) * length);
    int *maxFlow = (int *) malloc(sizeof(int) * length);
    int *minCost = (int *) malloc(sizeof(int) * length);
    int *offset = (int *) malloc(sizeof(int) * length);
    memset(offset, 0, sizeof(int) * length);
    result->values = (int *) malloc(sizeof(int) * 2);
    memset(result->values, 0, sizeof(int) * 2);
    result->length = 2;
    while (search(graphs, length, start, end, weights, parent, maxFlow, minCost, offset)) {
        result->values[0] += maxFlow[end];
        result->values[1] += maxFlow[end] * (minCost[end] - offset[start] + offset[end]);

        int index = end;
        while (index != start) {
            weights[parent[index]][index] -= maxFlow[end];
            weights[index][parent[index]] += maxFlow[end];
            index = parent[index];
        }
        for (int i = 0; i < length; ++i) {
            offset[i] += minCost[i];
        }
    }
}

static int search(pNode *graphs, int length, int start, int end, int **weights, int *parent, int *maxFlow, int *minCost, int *offset) {
    for (int i = 0; i < length; ++i) {
        parent[i] = -1;
        maxFlow[i] = ~(1 << 31);
        minCost[i] = ~(1 << 31);
    }
    minCost[start] = 0;

    int *visited = (int *) malloc(sizeof(int) * length);
    memset(visited, 0, sizeof(int) * length);
    QueueNode *queue = createQueue(length);
    enqueue(queue, start, minCost[start]);
    while (queue->length) {
        HeapNode heap = dequeue(queue);
        int index = heap.index;
        visited[index] = 1;
        EdgeNode *edge = graphs[index]->next;
        while (edge) {
            int edgeIndex = edge->index;
            if (weights[index][edgeIndex] && !visited[edgeIndex] && minCost[edgeIndex] > minCost[index] + edge->price + offset[index] - offset[edgeIndex]) {
                parent[edgeIndex] = index;
                maxFlow[edgeIndex] = min(maxFlow[index], weights[index][edgeIndex]);
                minCost[edgeIndex] = minCost[index] + edge->price + offset[index] - offset[edgeIndex];
                enqueue(queue, edgeIndex, minCost[edgeIndex]);
            }
            edge = edge->next;
        }
    }
    return (~(1 << 31) != minCost[end]) ? 1 : 0;
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

static void enqueue(QueueNode *queue, int index, int price) {
    int child = queue->length;
    while (child > 0) {
        int parent = (child - 1) >> 1;
        if (queue->values[parent].price <= price) {
            break;
        }
        queue->values[child] = queue->values[parent];
        child = parent;
    }
    queue->values[child].index = index;
    queue->values[child].price = price;
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

        if (child < queue->length - 1 && queue->values[child].price > queue->values[child + 1].price) {
            ++child;
        }
        if (queue->values[child].price >= pivot.price) {
            break;
        }
        queue->values[parent] = queue->values[child];
        parent = child;
    }
    queue->values[parent] = pivot;
    return value;
}
