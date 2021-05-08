#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *values;
    int length;
} ArrayNode;

typedef struct {
    ArrayNode *values;
    int length;
    int capacity;
} DoublyArrayNode;

typedef struct node {
    int values[2];
    int index;
    int weight;
    struct node *parent;
} HeapNode;

typedef HeapNode *pNode;

typedef struct {
    pNode *values;
    int length;
    int capacity;
} QueueNode;

static void search(int **graphs, int rowLength, int colLength, QueueNode *queue, int **visited, pNode parent, int row, int col, int *end);
static int getDistance(int row1, int col1, int row2, int col2);
static void reverse(DoublyArrayNode *values);
static QueueNode *createQueue();
static void enqueue(QueueNode *queue, int row, int col, int index, int weight, pNode parent);
static pNode dequeue(QueueNode *queue);

void aStar(int **graphs, int rowLength, int colLength, int *start, int *end, DoublyArrayNode *result) {
    int **visited = (int **) malloc(sizeof(int *) * rowLength);
    for (int i = 0; i < rowLength; ++i) {
        visited[i] = (int *) malloc(sizeof(int) * colLength);
        memset(visited[i], 0, sizeof(int) * colLength);
    }
    visited[start[0]][start[1]] = 1;

    QueueNode *queue = createQueue();
    enqueue(queue, start[0], start[1], 0, getDistance(start[0], start[1], end[0], end[1]), NULL);
    while (queue->length) {
        pNode heap = dequeue(queue);
        if (heap->values[0] == end[0] && heap->values[1] == end[1]) {
            result->values = (ArrayNode *) malloc(sizeof(ArrayNode) * 64);
            for (int i = 0; i < 64; ++i) {
                result->values[i].values = NULL;
                result->values[i].length = 0;
            }
            result->length = 0;
            result->capacity = 64;
            while (heap) {
                if (result->length >= result->capacity) {
                    result->values = (ArrayNode *) realloc(result->values, sizeof(ArrayNode) * (result->capacity + 16));
                    for (int i = result->capacity; i < result->capacity + 16; ++i) {
                        result->values[i].values = NULL;
                        result->values[i].length = 0;
                    }
                    result->capacity += 16;
                }
                result->values[result->length].values = (int *) malloc(sizeof(int) * 2);
                result->values[result->length].values[0] = heap->values[0];
                result->values[result->length].values[1] = heap->values[1];
                result->values[result->length].length = 2;
                ++result->length;

                heap = heap->parent;
            }
            reverse(result);
            return;
        }

        search(graphs, rowLength, colLength, queue, visited, heap, heap->values[0] + 1, heap->values[1], end);
        search(graphs, rowLength, colLength, queue, visited, heap, heap->values[0], heap->values[1] + 1, end);
        search(graphs, rowLength, colLength, queue, visited, heap, heap->values[0] - 1, heap->values[1], end);
        search(graphs, rowLength, colLength, queue, visited, heap, heap->values[0], heap->values[1] - 1, end);
    }
    result->values = NULL;
    result->length = 0;
}

static void search(int **graphs, int rowLength, int colLength, QueueNode *queue, int **visited, pNode parent, int row, int col, int *end) {
    if (row >= 0 && row < rowLength && col >= 0 && col < colLength && graphs[row][col] && !visited[row][col]) {
        enqueue(queue, row, col, parent->index + 1, getDistance(row, col, end[0], end[1]), parent);
        visited[row][col] = 1;
    }
}

static int getDistance(int row1, int col1, int row2, int col2) {
    return abs(row2 - row1) + abs(col2 - col1);
}

static void reverse(DoublyArrayNode *values) {
    int start = 0;
    int end = values->length - 1;
    while (start < end) {
        ArrayNode aux = values->values[start];
        values->values[start] = values->values[end];
        values->values[end] = aux;

        ++start;
        --end;
    }
}

static QueueNode *createQueue() {
    QueueNode *queue = (QueueNode *) malloc(sizeof(QueueNode));
    queue->values = (pNode *) malloc(sizeof(pNode) * 64);
    for (int i = 0; i < 64; ++i) {
        queue->values[i] = NULL;
    }
    queue->length = 0;
    queue->capacity = 64;
    return queue;
}

static void enqueue(QueueNode *queue, int row, int col, int index, int weight, pNode parent) {
    if (queue->length >= queue->capacity) {
        queue->values = (pNode *) realloc(queue->values, sizeof(pNode) * (queue->capacity + 16));
        for (int i = queue->capacity; i < queue->capacity + 16; ++i) {
            queue->values[i] = NULL;
        }
        queue->capacity += 16;
    }

    weight += index;
    pNode node = (pNode) malloc(sizeof(HeapNode));
    node->values[0] = row;
    node->values[1] = col;
    node->index = index;
    node->weight = weight;
    node->parent = parent;
    int child = queue->length;
    while (child > 0) {
        int parent = (child - 1) >> 1;
        if (queue->values[parent]->weight <= weight) {
            break;
        }
        queue->values[child] = queue->values[parent];
        child = parent;
    }
    queue->values[child] = node;
    ++queue->length;
}

static pNode dequeue(QueueNode *queue) {
    --queue->length;
    pNode value = queue->values[0];
    pNode pivot = queue->values[queue->length];
    int parent = 0;
    while (1) {
        int child = (parent << 1) + 1;
        if (child >= queue->length) {
            break;
        }

        if (child < queue->length - 1 && queue->values[child]->weight > queue->values[child + 1]->weight) {
            ++child;
        }
        if (queue->values[child]->weight >= pivot->weight) {
            break;
        }
        queue->values[parent] = queue->values[child];
        parent = child;
    }
    queue->values[parent] = pivot;
    return value;
}
