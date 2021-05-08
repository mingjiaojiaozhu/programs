#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    int degree;
    struct node *child;
    struct node *parent;
    struct node *next;
} TreeNode;

typedef TreeNode *pNode;

static pNode createNode(int value);
static pNode combine(pNode node1, pNode node2);
static pNode merge(pNode node1, pNode node2);
static pNode reverse(pNode node);
static pNode search(pNode node, int value);
static void increase(pNode node);
static void decrease(pNode node);
static void link(pNode parent, pNode child);
static void swap(int *p, int *q);

int isEmpty(pNode root) {
    return !root ? 1 : 0;
}

void add(pNode *root, int value) {
    if (!search(*root, value)) {
        *root = !*root ? createNode(value) : combine(*root, createNode(value));
    }
}

void erase(pNode *root, int value) {
    pNode node = search(*root, value);
    if (!node) {
        return;
    }

    pNode parent = node->parent;
    while (parent) {
        swap(&node->value, &parent->value);

        node = parent;
        parent = node->parent;
    }

    pNode pivot = NULL;
    pNode current = *root;
    while (current != node) {
        pivot = current;
        current = current->next;
    }

    if (pivot) {
        pivot->next = node->next;
    } else {
        *root = node->next;
    }
    *root = combine(*root, reverse(node->child));
}

void set(pNode *root, int target, int value) {
    pNode node = search(*root, target);
    if (node && target != value && !search(*root, value)) {
        node->value = value;
        if (target < value) {
            increase(node);
        } else {
            decrease(node);
        }
    }
}

int getRoot(pNode root) {
    if (!root) {
        return 1 << 31;
    }

    pNode pivot = root;
    pNode current = root->next;
    while (current) {
        if (pivot->value > current->value) {
            pivot = current;
        }
        current = current->next;
    }
    return pivot->value;
}

int contains(pNode root, int value) {
    return search(root, value) ? 1 : 0;
}

void clear(pNode *root) {
    *root = NULL;
}

static pNode createNode(int value) {
    pNode node = (pNode) malloc(sizeof(TreeNode));
    node->value = value;
    node->degree = 0;
    node->child = NULL;
    node->parent = NULL;
    node->next = NULL;
    return node;
}

static pNode combine(pNode node1, pNode node2) {
    pNode head = merge(node1, node2);
    if (!head) {
        return head;
    }

    pNode parent = NULL;
    pNode current = head;
    while (current->next) {
        pNode next = current->next;
        if ((current->degree != next->degree) || (next->next && next->degree == next->next->degree)) {
            parent = current;
            current = next;
        } else if (current->value <= next->value) {
            current->next = next->next;
            link(current, next);
        } else {
            if (!parent) {
                head = next;
            } else {
                parent->next = next;
            }
            link(next, current);
            current = next;
        }
    }
    return head;
}

static pNode merge(pNode node1, pNode node2) {
    if (!node1 || !node2) {
        return node1 ? node1 : node2;
    }

    pNode parent = NULL;
    pNode head = NULL;
    while (node1 && node2) {
        pNode pivot = NULL;
        if (node1->degree <= node2->degree) {
            pivot = node1;
            node1 = node1->next;
        } else {
            pivot = node2;
            node2 = node2->next;
        }

        if (!parent) {
            parent = pivot;
            head = pivot;
        } else {
            parent->next = pivot;
            parent = pivot;
        }
        pivot->next = node1 ? node1: node2;
    }
    return head;
}

static pNode reverse(pNode node) {
    if (!node) {
        return node;
    }

    node->parent = NULL;
    pNode tail = NULL;
    while (node->next) {
        pNode next = node->next;
        node->next = tail;
        tail = node;
        node = next;
        node->parent = NULL;
    }
    node->next = tail;
    return node;
}

static pNode search(pNode node, int value) {
    while (node) {
        if (value == node->value) {
            return node;
        }

        pNode child = search(node->child, value);
        if (child) {
            return child;
        }
        node = node->next;
    }
    return NULL;
}

static void increase(pNode node) {
    pNode child = node->child;
    while (child) {
        if (node->value < child->value) {
            child = child->next;
            continue;
        }

        pNode pivot = child;
        while (child->next) {
            if (child->next->value < pivot->value) {
                pivot = child->next;
            }
            child = child->next;
        }
        swap(&node->value, &pivot->value);

        node = pivot;
        child = node->child;
    }
}

static void decrease(pNode node) {
    pNode parent = node->parent;
    while (parent && node->value < parent->value) {
        swap(&node->value, &parent->value);

        node = parent;
        parent = node->parent;
    }
}

static void link(pNode parent, pNode child) {
    child->parent = parent;
    child->next = parent->child;
    parent->child = child;
    ++parent->degree;
}

static void swap(int *p, int *q) {
    *p ^= *q;
    *q ^= *p;
    *p ^= *q;
}
