#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node *left;
    struct node *right;
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

static QueueNode *createQueue();
static void enqueue(QueueNode *queue, pNode value);
static pNode dequeue(QueueNode *queue);
static int getLength(QueueNode queue);

int isPerfect(pNode root) {
    if (!root) {
        return 1;
    }

    QueueNode *queue = createQueue();
    enqueue(queue, root);

    int count = 0;
    int flag = 0;
    while (queue->head->next != queue->tail) {
        pNode current = dequeue(queue);
        if (!current) {
            flag = 1;
            continue;
        }

        if (flag) {
            return 0;
        }

        ++count;
        enqueue(queue, current->left);
        enqueue(queue, current->right);
    }
    return !(count & (count + 1)) ? 1 : 0;
}

int isCompleted(pNode root) {
    if (!root) {
        return 1;
    }

    QueueNode *queue = createQueue();
    enqueue(queue, root);

    int flag = 0;
    while (queue->head->next != queue->tail) {
        pNode current = dequeue(queue);
        if ((!current->left && current->right) || (flag && (current->left || current->right))) {
            return 0;
        }

        if (current->left) {
            enqueue(queue, current->left);
        }
        if (current->right) {
            enqueue(queue, current->right);
        } else {
            flag = 1;
        }
    }
    return 1;
}

int isFull(pNode root) {
    if (!root) {
        return 1;
    }

    QueueNode *queue = createQueue();
    enqueue(queue, root);
    while (queue->head->next != queue->tail) {
        pNode current = dequeue(queue);
        if ((current->left && !current->right) || (!current->left && current->right)) {
            return 0;
        }

        if (current->left) {
            enqueue(queue, current->left);
        }
        if (current->right) {
            enqueue(queue, current->right);
        }
    }
    return 1;
}

int nodeNum(pNode root) {
    if (!root) {
        return 0;
    }

    QueueNode *queue = createQueue();
    enqueue(queue, root);

    int count = 0;
    while (queue->head->next != queue->tail) {
        ++count;

        pNode current = dequeue(queue);
        if (current->left) {
            enqueue(queue, current->left);
        }
        if (current->right) {
            enqueue(queue, current->right);
        }
    }
    return count;
}

int leafNodeNum(pNode root) {
    if (!root) {
        return 0;
    }

    QueueNode *queue = createQueue();
    enqueue(queue, root);

    int count = 0;
    while (queue->head->next != queue->tail) {
        pNode current = dequeue(queue);
        if (!current->left && !current->right) {
            ++count;
            continue;
        }

        if (current->left) {
            enqueue(queue, current->left);
        }
        if (current->right) {
            enqueue(queue, current->right);
        }
    }
    return count;
}

int maxDepth(pNode root) {
    if (!root) {
        return 0;
    }

    QueueNode *queue = createQueue();
    enqueue(queue, root);

    int count = 0;
    while (queue->head->next != queue->tail) {
        ++count;

        int length = getLength(*queue);
        for (int i = 0; i < length; ++i) {
            pNode current = dequeue(queue);
            if (current->left) {
                enqueue(queue, current->left);
            }
            if (current->right) {
                enqueue(queue, current->right);
            }
        }
    }
    return count;
}

pNode mirror(pNode root) {
    if (!root || (!root->left && !root->right)) {
        return root;
    }

    pNode aux = root->left;
    root->left = root->right;
    root->right = aux;

    root->left = mirror(root->left);
    root->right = mirror(root->right);
    return root;
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

static int getLength(QueueNode queue) {
    ListNode *current = queue.head;
    int count = 0;
    while (current->next != queue.tail) {
        ++count;
        current = current->next;
    }
    return count;
}
