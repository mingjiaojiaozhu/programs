#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int key;
    int value;
    struct node *left;
    struct node *right;
} TreeNode;

typedef TreeNode *pNode;

static pNode createNode(int key, int value);
static void addNode(pNode parent, int key, int value);
static void eraseNode(pNode parent, pNode current, pNode child);

int isEmpty(pNode root) {
    return !root ? 1 : 0;
}

void add(pNode *root, int key, int value) {
    if (!*root) {
        *root = createNode(key, value);
        return;
    }

    pNode parent = NULL;
    pNode current = *root;
    while (current) {
        if (key == current->key) {
            current->value = value;
            return;
        }

        parent = current;
        if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    addNode(parent, key, value);
}

void erase(pNode *root, int key) {
    if (!*root) {
        return;
    }

    if (key == (*root)->key && (!(*root)->left || !(*root)->right)) {
        *root = (*root)->left ? (*root)->left : (*root)->right;
        return;
    }

    pNode parent = NULL;
    pNode current = *root;
    while (current) {
        if (key == current->key) {
            break;
        }

        parent = current;
        if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (!current) {
        return;
    }

    if (!current->left || !current->right) {
        eraseNode(parent, current, current->left ? current->left : current->right);
        return;
    }

    pNode child = current->right;
    parent = current;
    while (child->left) {
        parent = child;
        child = child->left;
    }
    current->key = child->key;
    current->value = child->value;
    eraseNode(parent, child, child->right);
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
    node->left = NULL;
    node->right = NULL;
    return node;
}

static void addNode(pNode parent, int key, int value) {
    if (key < parent->key) {
        parent->left = createNode(key, value);
    } else {
        parent->right = createNode(key, value);
    }
}

static void eraseNode(pNode parent, pNode current, pNode child) {
    if (current == parent->left) {
        parent->left = child;
    } else {
        parent->right = child;
    }
}
