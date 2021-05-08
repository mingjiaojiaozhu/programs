#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int key;
    int value;
    int height;
    struct node *left;
    struct node *right;
} TreeNode;

typedef TreeNode *pNode;

static pNode createNode(int key, int value);
static pNode addNode(pNode parent, int key, int value);
static pNode eraseNode(pNode parent, int key);
static int getHeight(pNode current);
static pNode leftLeftRotation(pNode current);
static pNode rightRightRotation(pNode current);
static pNode leftRightRotation(pNode current);
static pNode rightLeftRotation(pNode current);
static int max(int i, int j);

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
    node->height = 1;
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
        if (getHeight(parent->left) - getHeight(parent->right) >= 2) {
            if (key < parent->left->key) {
                parent = leftLeftRotation(parent);
            } else {
                parent = leftRightRotation(parent);
            }
        }
    } else {
        parent->right = addNode(parent->right, key, value);
        if (getHeight(parent->right) - getHeight(parent->left) >= 2) {
            if (key > parent->right->key) {
                parent = rightRightRotation(parent);
            } else {
                parent = rightLeftRotation(parent);
            }
        }
    }
    parent->height = max(getHeight(parent->left), getHeight(parent->right)) + 1;
    return parent;
}

static pNode eraseNode(pNode parent, int key) {
    if (!parent) {
        return parent;
    }

    if (key == parent->key) {
        if (parent->left && parent->right) {
            pNode current = parent->right;
            while (current->left) {
                current = current->left;
            }
            parent->key = current->key;
            parent->value = current->value;
            parent->right = eraseNode(parent->right, key);
        } else {
            parent = parent->left ? parent->left : parent->right;
        }
    } else if (key < parent->key) {
        parent->left = eraseNode(parent->left, key);
        if (getHeight(parent->right) - getHeight(parent->left) >= 2) {
            if (getHeight(parent->right->right) > getHeight(parent->right->left)) {
                parent = rightRightRotation(parent);
            } else {
                parent = rightLeftRotation(parent);
            }
        }
    } else {
        parent->right = eraseNode(parent->right, key);
        if (getHeight(parent->left) - getHeight(parent->right) >= 2) {
            if (getHeight(parent->left->right) < getHeight(parent->left->left)) {
                parent = leftLeftRotation(parent);
            } else {
                parent = leftRightRotation(parent);
            }
        }
    }

    if (parent) {
        parent->height = max(getHeight(parent->left), getHeight(parent->right)) + 1;
    }
    return parent;
}

static int getHeight(pNode current) {
    if (!current) {
        return 0;
    }
    return current->height;
}

static pNode leftLeftRotation(pNode current) {
    pNode child = current->left;
    current->left = child->right;
    child->right = current;

    current->height = max(getHeight(current->left), getHeight(current->right)) + 1;
    child->height = max(getHeight(child->left), getHeight(child->right)) + 1;
    return child;
}

static pNode rightRightRotation(pNode current) {
    pNode child = current->right;
    current->right = child->left;
    child->left = current;

    current->height = max(getHeight(current->left), getHeight(current->right)) + 1;
    child->height = max(getHeight(child->left), getHeight(child->right)) + 1;
    return child;
}

static pNode leftRightRotation(pNode current) {
    current->left = rightRightRotation(current->left);
    return leftLeftRotation(current);
}

static pNode rightLeftRotation(pNode current) {
    current->right = leftLeftRotation(current->right);
    return rightRightRotation(current);
}

static int max(int i, int j) {
    int aux = ~((i > j) ? 1 : 0) + 1;
    return (i & aux) | (j & ~aux);
}
