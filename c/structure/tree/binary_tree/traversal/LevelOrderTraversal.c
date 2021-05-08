#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    int value;
    struct node *left;
    struct node *right;
} TreeNode;

typedef TreeNode *pNode;

typedef struct {
    int *values;
    int length;
    int capacity;
} ArrayNode;

typedef struct queue {
    pNode value;
    struct queue *prev;
    struct queue *next;
} ListNode;

typedef struct {
    ListNode *head;
    ListNode *tail;
} QueueNode;

static QueueNode *createQueue();
static void enqueue(QueueNode *queue, pNode value);
static pNode dequeue(QueueNode *queue);

void levelOrderTraversal(pNode root, ArrayNode *result) {
    result->values = (int *) malloc(sizeof(int) * 64);
    memset(result->values, 0, sizeof(int) * 64);
    result->length = 0;
    result->capacity = 64;

    QueueNode *queue = createQueue();
    enqueue(queue, root);
    while (queue->head->next != queue->tail) {
        pNode current = dequeue(queue);
        if (result->length >= result->capacity) {
            result->values = (int *) realloc(result->values, sizeof(int) * (result->capacity + 16));
            memset(result->values + result->capacity, 0, sizeof(int) * 16);
            result->capacity += 16;
        }
        result->values[result->length] = current->value;
        ++result->length;

        if (current->left) {
            enqueue(queue, current->left);
        }
        if (current->right) {
            enqueue(queue, current->right);
        }
    }
}

static QueueNode *createQueue() {
    QueueNode *queue = (QueueNode *) malloc(sizeof(QueueNode));
    queue->head = (ListNode *) malloc(sizeof(ListNode));
    queue->tail = (ListNode *) malloc(sizeof(ListNode));
    queue->head->value = NULL;
    queue->tail->value = NULL;
    queue->head->prev = NULL;
    queue->tail->prev = queue->head;
    queue->head->next = queue->tail;
    queue->tail->next = NULL;
    return queue;
}

static void enqueue(QueueNode *queue, pNode value) {
    ListNode *node = (ListNode *) malloc(sizeof(ListNode));
    node->value = value;
    node->prev = queue->tail->prev;
    node->next = queue->tail;
    queue->tail->prev->next = node;
    queue->tail->prev = node;
}

static pNode dequeue(QueueNode *queue) {
    ListNode *node = queue->head->next;
    node->next->prev = queue->head;
    queue->head->next = node->next;
    return node->value;
}
