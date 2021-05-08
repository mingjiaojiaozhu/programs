#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    int weight;
    struct node *left;
    struct node *right;
    char *code;
} TreeNode;

typedef TreeNode *pNode;

typedef struct {
    pNode *values;
    int length;
} QueueNode;

typedef struct stack {
    pNode value;
    struct stack *next;
} StackNode;

static pNode getRoot(char *text, int size, int minValue, pNode *arrays);
static pNode createNode(int weight, pNode left, pNode right);
static QueueNode *createQueue(int length);
static void enqueue(QueueNode *queue, pNode value);
static pNode dequeue(QueueNode *queue);
static StackNode *createStack();
static void pushStack(StackNode *stack, pNode value);
static pNode popStack(StackNode *stack);

void huffmanCoding(char *text, char **result) {
    int maxValue = text[0];
    int minValue = text[0];
    for (char *p = text + 1; '\0' != *p; ++p) {
        if (maxValue < *p) {
            maxValue = *p;
        }
        if (minValue > *p) {
            minValue = *p;
        }
    }
    pNode *arrays = (pNode *) malloc(sizeof(pNode) * (maxValue - minValue + 1));
    for (int i = 0; i < maxValue - minValue + 1; ++i) {
        arrays[i] = NULL;
    }

    pNode current = getRoot(text, maxValue - minValue + 1, minValue, arrays);
    StackNode *stack = createStack();
    while (current || stack->next) {
        while (current) {
            char *code = current->code;
            pushStack(stack, current);

            current = current->left;
            if (current) {
                sprintf(current->code, "%s0", code);
            }
        }

        current = popStack(stack);
        char *code = current->code;

        current = current->right;
        if (current) {
            sprintf(current->code, "%s1", code);
        }
    }

    *result = (char *) malloc(sizeof(char) * (strlen(text) << 3));
    memset(*result, '\0', sizeof(char) * (strlen(text) << 3));
    for (char *p = text; '\0' != *p; ++p) {
        sprintf(*result, "%s%s", *result, arrays[*p - minValue]->code);
    }
}

static pNode getRoot(char *text, int size, int minValue, pNode *arrays) {
    int *buckets = (int *) malloc(sizeof(int) * (size));
    memset(buckets, 0, sizeof(int) * (size));
    for (char *p = text; '\0' != *p; ++p) {
        ++buckets[*p - minValue];
    }

    QueueNode *queue = createQueue(size);
    for (int i = 0; i < size; ++i) {
        pNode node = createNode(buckets[i], NULL, NULL);
        enqueue(queue, node);
        arrays[i] = node;
    }

    while (queue->length > 1) {
        pNode left = dequeue(queue);
        pNode right = dequeue(queue);
        enqueue(queue, createNode(left->weight + right->weight, left, right));
    }
    return dequeue(queue);
}

static pNode createNode(int weight, pNode left, pNode right) {
    pNode node = (pNode) malloc(sizeof(TreeNode));
    node->weight = weight;
    node->left = left;
    node->right = right;
    node->code = (char *) malloc(sizeof(char) * 64);
    memset(node->code, '\0', sizeof(char) * 64);
    return node;
}

static QueueNode *createQueue(int length) {
    QueueNode *queue = (QueueNode *) malloc(sizeof(QueueNode));
    queue->values = (pNode *) malloc(sizeof(pNode) * length);
    for (int i = 0; i < length; ++i) {
        queue->values[i] = NULL;
    }
    queue->length = 0;
    return queue;
}

static void enqueue(QueueNode *queue, pNode value) {
    int child = queue->length;
    while (child > 0) {
        int parent = (child - 1) >> 1;
        if (queue->values[parent]->weight <= value->weight) {
            break;
        }
        queue->values[child] = queue->values[parent];
        child = parent;
    }
    queue->values[child] = value;
    ++queue->length;
}

static pNode dequeue(QueueNode *queue) {
    pNode value = queue->values[0];
    --queue->length;
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

static StackNode *createStack() {
    StackNode *stack = (StackNode *) malloc(sizeof(StackNode));
    stack->value = NULL;
    stack->next = NULL;
    return stack;
}

static void pushStack(StackNode *stack, pNode value) {
    StackNode *node = (StackNode *) malloc(sizeof(StackNode));
    node->value = value;
    node->next = stack->next;
    stack->next = node;
}

static pNode popStack(StackNode *stack) {
    StackNode *node = stack->next;
    stack->next = node->next;
    return node->value;
}
