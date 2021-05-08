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

typedef struct queue {
    int value;
    struct queue *prev;
    struct queue *next;
} ListNode;

typedef struct {
    ListNode *head;
    ListNode *tail;
} QueueNode;

static QueueNode *createQueue();
static void enqueue(QueueNode *queue, int value);
static int dequeue(QueueNode *queue);

void spfa(pNode *graphs, int length, int start, ArrayNode *result) {
    int *visited = (int *) malloc(sizeof(int) * length);
    memset(visited, 0, sizeof(int) * length);
    QueueNode *queue = createQueue();
    enqueue(queue, start);

    result->values = (int *) malloc(sizeof(int) * length);
    for (int i = 0; i < length; ++i) {
        result->values[i] = ~(1 << 31);
    }
    result->length = length;
    result->values[start] = 0;

    int count = 0;
    while (queue->head->next != queue->tail) {
        int index = dequeue(queue);
        visited[index] = 0;

        EdgeNode *edge = graphs[index]->next;
        while (edge) {
            int edgeIndex = edge->index;
            int edgeWeight = edge->weight;
            if (result->values[edgeIndex] > result->values[index] + edgeWeight) {
                result->values[edgeIndex] = result->values[index] + edgeWeight;
                if (!visited[edgeIndex]) {
                    enqueue(queue, edgeIndex);
                    visited[edgeIndex] = 1;
                    ++count;
                }
            }
            edge = edge->next;
        }
        if (count >= length) {
            result->values = NULL;
            result->length = 0;
            return;
        }
    }
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
