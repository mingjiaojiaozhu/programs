#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *values;
    int length;
} ArrayNode;

typedef struct node {
    struct node **next;
    struct node *failure;
    ArrayNode *indexes;
} TreeNode;

typedef TreeNode *pNode;

typedef struct queue {
    pNode value;
    struct queue *prev;
    struct queue *next;
} ListNode;

typedef struct {
    ListNode *head;
    ListNode *tail;
} QueueNode;

static pNode getRoot(char **patterns, int length);
static pNode createTreeNode(int length);
static QueueNode *createQueue();
static void enqueue(QueueNode *queue, pNode value);
static pNode dequeue(QueueNode *queue);

void ahoCorasick(char *text, char **patterns, int length, ArrayNode *result) {
    pNode root = getRoot(patterns, length);

    result->values = (int *) malloc(sizeof(int) * length);
    for (int i = 0; i < length; ++i) {
        result->values[i] = -1;
    }
    result->length = length;
    pNode current = root;
    for (char *p = text; '\0' != *p; ++p) {
        pNode aux = NULL;
        while (!aux) {
            aux = current->next[*p - 'a'];
            if (current == root) {
                break;
            }

            if (!aux) {
                current = current->failure;
            }
        }
        if (aux) {
            current = aux;
        }

        for (int i = 0; i < current->indexes->length; ++i) {
            result->values[current->indexes->values[i]] = p - text - strlen(patterns[current->indexes->values[i]]) + 1;
        }
    }
}

static pNode getRoot(char **patterns, int length) {
    pNode root = createTreeNode(0);
    for (int i = 0; i < length; ++i) {
        int patternLength = strlen(patterns[i]);
        pNode current = root;
        for (char *p = patterns[i]; '\0' != *p; ++p) {
            int index = *p - 'a';
            if (!current->next[index]) {
                current->next[index] = createTreeNode(patternLength);
            }
            current = current->next[index];
        }
        current->indexes->values[current->indexes->length] = i;
        ++current->indexes->length;
    }

    QueueNode *queue = createQueue();
    for (int i = 0; i < 26; ++i) {
        if (root->next[i]) {
            root->next[i]->failure = root;
            enqueue(queue, root->next[i]);
        }
    }
    while (queue->head->next != queue->tail) {
        pNode current = dequeue(queue);
        for (int i = 0; i < 26; ++i) {
            if (!current->next[i]) {
                continue;
            }

            pNode child = current->next[i];
            pNode failure = current->failure;
            while (failure && !failure->next[i]) {
                failure = failure->failure;
            }
            if (!failure) {
                child->failure = root;
            } else {
                child->failure = failure->next[i];
                for (int j = 0; j < failure->next[i]->indexes->length; ++j) {
                    child->indexes->values[child->indexes->length] = failure->next[i]->indexes->values[j];
                    ++child->indexes->length;
                }
            }
            enqueue(queue, child);
        }
    }
    return root;
}

static pNode createTreeNode(int length) {
    pNode node = (pNode) malloc(sizeof(TreeNode));
    node->next = (pNode *) malloc(sizeof(pNode) * 26);
    for (int i = 0; i < 26; ++i) {
        node->next[i] = NULL;
    }
    node->failure = NULL;
    node->indexes = (ArrayNode *) malloc(sizeof(ArrayNode));
    node->indexes->values = (int *) malloc(sizeof(int) * length);
    memset(node->indexes->values, 0, sizeof(int) * length);
    node->indexes->length = 0;
    return node;
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
