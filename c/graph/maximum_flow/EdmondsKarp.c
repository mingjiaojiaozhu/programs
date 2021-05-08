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

typedef struct queue {
    int value;
    struct queue *prev;
    struct queue *next;
} ListNode;

typedef struct {
    ListNode *head;
    ListNode *tail;
} QueueNode;

static int search(pNode *graphs, int length, int start, int end, int **weights, int *parent, int *maxFlow);
static int min(int i, int j);
static QueueNode *createQueue();
static void enqueue(QueueNode *queue, int value);
static int dequeue(QueueNode *queue);

int edmondsKarp(pNode *graphs, int length, int start, int end) {
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
    for (int i = 0; i < length; ++i) {
        maxFlow[i] = ~(1 << 31);
    }
    int result = 0;
    while (1) {
        int value = search(graphs, length, start, end, weights, parent, maxFlow);
        if (!~value) {
            break;
        }

        int index = end;
        while (index != start) {
            weights[parent[index]][index] -= value;
            weights[index][parent[index]] += value;
            index = parent[index];
        }
        result += value;
    }
    return result;
}

static int search(pNode *graphs, int length, int start, int end, int **weights, int *parent, int *maxFlow) {
    for (int i = 0; i < length; ++i) {
        parent[i] = -1;
    }
    QueueNode *queue = createQueue();
    enqueue(queue, start);
    while (queue->head->next != queue->tail) {
        int index = dequeue(queue);
        EdgeNode *edge = graphs[index]->next;
        while (edge) {
            int edgeIndex = edge->index;
            if (weights[index][edgeIndex] && !~parent[edgeIndex]) {
                parent[edgeIndex] = index;
                maxFlow[edgeIndex] = min(weights[index][edgeIndex], maxFlow[index]);
                enqueue(queue, edgeIndex);
            }
            edge = edge->next;
        }
    }
    return ~parent[end] ? maxFlow[end] : -1;
}

static int min(int i, int j) {
    int aux = ~((i > j) ? 1 : 0) + 1;
    return (i & ~aux) | (j & aux);
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
