#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node {
    int key;
    int value;
    int factor;
    struct node *left;
    struct node *right;
} TreeNode;

typedef TreeNode *pNode;

static pNode createNode(int key, int value);
static pNode addNode(pNode parent, int key, int value);
static pNode eraseNode(pNode parent, int key);
static pNode leftRotation(pNode current);
static pNode rightRotation(pNode current);

int isEmpty(pNode root) {
    return !root ? 1 : 0;
}

void add(pNode *root, int key, int value) {
    *root = addNode(*root, key, value);
}

void erase(pNode *root, int key) {
    *root = eraseNode(*root, key);
}

void set(pNode *root, int key, int value) {
    pNode current = *root;
    while (current) {
        if (key == current->key) {
            current->value = value;
            return;
        }

        if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
}

int get(pNode root, int key) {
    pNode current = root;
    while (current) {
        if (key == current->key) {
            return current->value;
        }

        if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return 1 << 31;
}

void clear(pNode *root) {
    *root = NULL;
}

static pNode createNode(int key, int value) {
    pNode node = (pNode) malloc(sizeof(TreeNode));
    node->key = key;
    node->value = value;
    srand((unsigned int) time(NULL));
    node->factor = rand() % 65536;
    node->left = NULL;
    node->right = NULL;
    return node;
}

static pNode addNode(pNode parent, int key, int value) {
    if (!parent) {
        pNode node = createNode(key, value);
        return node;
    }

    if (key == parent->key) {
        parent->value = value;
        return parent;
    }

    if (key < parent->key) {
        parent->left = addNode(parent->left, key, value);
        if (parent->factor < parent->left->factor) {
            parent = rightRotation(parent);
        }
    } else {
        parent->right = addNode(parent->right, key, value);
        if (parent->factor < parent->right->factor) {
            parent = leftRotation(parent);
        }
    }
    return parent;
}

static pNode eraseNode(pNode parent, int key) {
    if (!parent) {
        return parent;
    }

    if (key == parent->key) {
        if (parent->left && parent->right) {
            if (parent->left->factor > parent->right->factor) {
                parent = rightRotation(parent);
                parent->right = eraseNode(parent->right, key);
            } else {
                parent = leftRotation(parent);
                parent->left = eraseNode(parent->left, key);
            }
        } else {
            parent = parent->left ? parent->left : parent->right;
        }
    } else if (key < parent->key) {
        parent->left = eraseNode(parent->left, key);
    } else {
        parent->right = eraseNode(parent->right, key);
    }
    return parent;
}

static pNode leftRotation(pNode current) {
    pNode child = current->left;
    current->left = child->right;
    child->right = current;
    return child;
}

static pNode rightRotation(pNode current) {
    pNode child = current->right;
    current->right = child->left;
    child->left = current;
    return child;
}
