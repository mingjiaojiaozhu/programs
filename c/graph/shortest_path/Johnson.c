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

typedef struct {
    int index;
    int weight;
} HeapNode;

typedef struct {
    HeapNode *values;
    int length;
} QueueNode;

static int *bellmanFord(pNode *graphs, int length, int start);
static int *dijkstra(pNode *graphs, int length, int start);
static QueueNode *createQueue(int length);
static void enqueue(QueueNode *queue, int index, int weight);
static HeapNode dequeue(QueueNode *queue);

void johnson(pNode *graphs, int length, DoublyArrayNode *result) {
    pNode *aux = (pNode *) malloc(sizeof(pNode) * (length + 1));
    for (int i = 0; i < length; ++i) {
        aux[i] = graphs[i];
    }
    aux[length] = (pNode) malloc(sizeof(VertexNode));
    aux[length]->value = 0;
    aux[length]->next = NULL;
    for (int i = length - 1; i >= 0; --i) {
        EdgeNode *edge = (EdgeNode *) malloc(sizeof(EdgeNode));
        edge->index = i;
        edge->weight = 0;
        edge->next = aux[length]->next;
        aux[length]->next = edge;
    }

    int *reWeight = bellmanFord(aux, length + 1, length);
    if (!reWeight) {
        result->values = NULL;
        result->length = 0;
        return;
    }

    for (int i = 0; i < length; ++i) {
        EdgeNode *edge = graphs[i]->next;
        while (edge) {
            edge->weight += reWeight[i] - reWeight[edge->index];
            edge = edge->next;
        }
    }

    result->values = (ArrayNode *) malloc(sizeof(ArrayNode) * length);
    for (int i = 0; i < length; ++i) {
        result->values[i].values = dijkstra(graphs, length, i);
        result->values[i].length = length;
        for (int j = 0; j < length; ++j) {
            if (~(1 << 31) != result->values[i].values[j]) {
                result->values[i].values[j] += reWeight[j] - reWeight[i];
            }
        }
    }
    result->length = length;
}

static int *bellmanFord(pNode *graphs, int length, int start) {
    int *result = (int *) malloc(sizeof(int) * length);
    for (int i = 0; i < length; ++i) {
        result[i] = ~(1 << 31);
    }
    result[start] = 0;

    int index = start;
    for (int i = 0; i < length; ++i) {
        EdgeNode *edge = graphs[index]->next;
        while (edge) {
            int pivot = result[index] + edge->weight;
            int edgeIndex = edge->index;
            if (~(1 << 31) != result[index] && pivot < result[edgeIndex]) {
                result[edgeIndex] = pivot;
            }
            edge = edge->next;
        }

        ++index;
        if (index >= length) {
            index = 0;
        }
    }

    index = start;
    for (int i = 0; i < length; ++i) {
        EdgeNode *edge = graphs[index]->next;
        while (edge) {
            int pivot = result[index] + edge->weight;
            int edgeIndex = edge->index;
            if (~(1 << 31) != result[index] && pivot < result[edgeIndex]) {
                return NULL;
            }
            edge = edge->next;
        }

        ++index;
        if (index >= length) {
            index = 0;
        }
    }
    return result;
}

static int *dijkstra(pNode *graphs, int length, int start) {
    int *visited = (int *) malloc(sizeof(int) * length);
    memset(visited, 0 , sizeof(int) * length);
    QueueNode *queue = createQueue(length);
    enqueue(queue, start, 0);

    int *result = (int *) malloc(sizeof(int) * length);
    for (int i = 0; i < length; ++i) {
        result[i] = ~(1 << 31);
    }
    while (queue->length) {
        HeapNode heap = dequeue(queue);
        int index = heap.index;
        int weight = heap.weight;
        if (visited[index]) {
            continue;
        }

        result[index] = weight;
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
    return result;
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
