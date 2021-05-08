#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node *child;
    struct node *parent;
    struct node *next;
} TreeNode;

typedef TreeNode *pNode;

static pNode createNode(int value);
static pNode merge(pNode node1, pNode node2);
static pNode combine(pNode node);
static pNode search(pNode node, int value);
static void increase(pNode node);
static void decrease(pNode *root, pNode node);

int isEmpty(pNode root) {
    return !root ? 1 : 0;
}

void add(pNode *root, int value) {
    if (!search(*root, value)) {
        *root = !*root ? createNode(value) : merge(*root, createNode(value));
    }
}

void erase(pNode *root, int value) {
    pNode node = search(*root, value);
    if (!node) {
        return;
    }

    if (value != (*root)->value) {
        node->value = (*root)->value - 1;
        decrease(root, node);
    }

    pNode current = *root;
    if (!current->child) {
        *root = NULL;
    } else {
        pNode child = current->child;
        child->parent = NULL;
        *root = combine(child);
    }
}

void set(pNode *root, int target, int value) {
    pNode node = search(*root, target);
    if (node && target != value && !search(*root, value)) {
        node->value = value;
        if (target < value) {
            increase(node);
        } else {
            decrease(root, node);
        }
    }
}

int getRoot(pNode root) {
    if (root) {
        return root->value;
    }
    return 1 << 31;
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
    node->child = NULL;
    node->parent = NULL;
    node->next = NULL;
    return node;
}

static pNode merge(pNode node1, pNode node2) {
    if (!node1 || !node2) {
        return node1 ? node1 : node2;
    }

    if (node1->value < node2->value) {
        pNode next = node2->next;
        node1->next = next;
        if (next) {
            next->parent = node1;
        }

        pNode child = node1->child;
        node2->parent = node1;
        node2->next = child;
        if (child) {
            child->parent = node2;
        }
        node1->child = node2;
        return node1;
    }

    pNode parent = node1->parent;
    node2->parent = parent;
    if (parent && parent->child != node1) {
        parent->next = node2;
    }

    pNode child = node2->child;
    node1->parent = node2;
    node1->next = child;
    if (child) {
        child->parent = node1;
    }
    node2->child = node1;
    return node2;
}

static pNode combine(pNode node) {
    pNode current = node;
    pNode next = current->next;
    pNode tail = current;

    int flag = 1;
    while (next) {
        tail = merge(current, next);
        current = tail->next;
        next = current ? current->next : NULL;

        if (!flag && !current) {
            break;
        }
        flag = 0;
    }

    if (current) {
        tail = current;
    }

    pNode parent = tail->parent;
    while (parent) {
        tail = merge(parent, tail);
        parent = tail->parent;
    }
    return tail;
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
    int pivot = node->value;
    while (node->child && pivot < node->child->value) {
        node->value = node->child->value;
        node = node->child;
    }
    node->value = pivot;
}

static void decrease(pNode *root, pNode node) {
    pNode parent = node->parent;
    if (parent->child == node) {
        parent->child = node->next;
    } else {
        parent->next = node->next;
    }
    if (node->next) {
        node->next->parent = parent;
    }

    node->parent = NULL;
    node->next = NULL;
    *root = merge(node, *root);
}
