#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *values;
    int length;
} ArrayNode;

typedef struct node {
    int weight;
    int level;
    struct node *parent;
    int marked;
} HeapNode;

typedef HeapNode *pNode;

typedef struct {
    pNode *values;
    int length;
    int capacity;
} QueueNode;

static void reverse(ArrayNode *values);
static QueueNode *createQueue();
static void enqueue(QueueNode *queue, int weight, int level, pNode parent, int left);
static pNode dequeue(QueueNode *queue);

void optimalLoading(int *weights, int length, int target, ArrayNode *result) {
    int *aux = (int *) malloc(sizeof(int) * length);
    memset(aux, 0, sizeof(int) * length);
    for (int i = length - 1; i > 0; --i) {
        aux[i - 1] = aux[i] + weights[i];
    }

    QueueNode *queue = createQueue();
    int weight = 0;
    int level = 0;
    pNode current = NULL;
    while (level != length) {
        if (weight + weights[level] <= target) {
            enqueue(queue, weight + weights[level] + aux[level], level + 1, current, 1);
        }
        enqueue(queue, weight + aux[level], level + 1, current, 0);

        current = dequeue(queue);
        level = current->level;
        weight = current->weight - aux[level - 1];
    }

    result->values = (int *) malloc(sizeof(int) * length);
    memset(result->values, 0, sizeof(int) * length);
    result->length = 0;
    for (int i = length - 1; i >= 0; --i) {
        if (current->marked) {
            result->values[result->length] = weights[i];
            ++result->length;
        }
        current = current->parent;
    }
    reverse(result);
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

static void enqueue(QueueNode *queue, int weight, int level, pNode parent, int marked) {
    if (queue->length >= queue->capacity) {
        queue->values = (pNode *) realloc(queue->values, sizeof(pNode) * (queue->capacity + 16));
        for (int i = queue->capacity; i < queue->capacity + 16; ++i) {
            queue->values[i] = NULL;
        }
        queue->capacity += 16;
    }

    pNode node = (pNode) malloc(sizeof(HeapNode));
    node->weight = weight;
    node->level = level;
    node->parent = parent;
    node->marked = marked;
    int child = queue->length;
    while (child > 0) {
        int parent = (child - 1) >> 1;
        if (queue->values[parent]->weight >= weight) {
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

        if (child < queue->length - 1 && queue->values[child]->weight < queue->values[child + 1]->weight) {
            ++child;
        }
        if (queue->values[child]->weight <= pivot->weight) {
            break;
        }
        queue->values[parent] = queue->values[child];
        parent = child;
    }
    queue->values[parent] = pivot;
    return value;
}
