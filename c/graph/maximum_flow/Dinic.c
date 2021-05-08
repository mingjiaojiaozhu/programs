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

static int searchOfBFS(pNode *graphs, int length, int start, int end, int **weights, int *parent);
static int searchOfDFS(pNode *graphs, int length, int start, int end, int minValue, int **weights, int *parent);
static int min(int i, int j);
static QueueNode *createQueue();
static void enqueue(QueueNode *queue, int value);
static int dequeue(QueueNode *queue);

int dinic(pNode *graphs, int length, int start, int end) {
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
    int result = 0;
    while (searchOfBFS(graphs, length, start, end, weights, parent)) {
        result += searchOfDFS(graphs, length, start, end, ~(1 << 31), weights, parent);
    }
    return result;
}

static int searchOfBFS(pNode *graphs, int length, int start, int end, int **weights, int *parent) {
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
                enqueue(queue, edgeIndex);
            }
            edge = edge->next;
        }
    }
    return ~parent[end] ? 1 : 0;
}

static int searchOfDFS(pNode *graphs, int length, int start, int end, int flow, int **weights, int *parent) {
    if (start == end) {
        return flow;
    }

    EdgeNode *edge = graphs[start]->next;
    while (edge) {
        int edgeIndex = edge->index;
        if (weights[start][edgeIndex] && parent[edgeIndex] == start) {
            int value = searchOfDFS(graphs, length, edgeIndex, end, min(flow, weights[start][edgeIndex]), weights, parent);
            if (value) {
                weights[start][edgeIndex] -= value;
                weights[edgeIndex][start] += value;
                return value;
            }
        }
        edge = edge->next;
    }
    return 0;
}

static int min(int i, int j) {
    int weights = ~((i > j) ? 1 : 0) + 1;
    return (i & ~weights) | (j & weights);
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
