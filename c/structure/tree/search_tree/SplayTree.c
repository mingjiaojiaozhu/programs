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
static pNode addNode(pNode parent, int key, int value);
static void eraseNode(pNode parent, pNode current, pNode child);
static void splay(pNode *root, pNode pivot);
static pNode leftRotation(pNode current);
static pNode rightRotation(pNode current);

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
            splay(root, current);
            return;
        }

        parent = current;
        if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    current = addNode(parent, key, value);
    splay(root, current);
}

void erase(pNode *root, int key) {
    if (!*root) {
        return;
    }

    if (key == (*root)->key && (!(*root)->left || !(*root)->right)) {
        *root = (*root)->left ? (*root)->left : (*root)->right;
        return;
    }

    pNode current = *root;
    while (current) {
        if (key == current->key) {
            break;
        }

        if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (!current) {
        return;
    }

    splay(root, current);
    if (!current->left || !current->right) {
        *root = current->left ? current->left : current->right;
        return;
    }

    pNode child = current->right;
    pNode parent = current;
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
            splay(root, current);
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

int get(pNode *root, int key) {
    pNode current = *root;
    while (current) {
        if (key == current->key) {
            splay(root, current);
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

static pNode addNode(pNode parent, int key, int value) {
    pNode child = createNode(key, value);
    if (key < parent->key) {
        parent->left = child;
    } else {
        parent->right = child;
    }
    return child;
}

static void eraseNode(pNode parent, pNode current, pNode child) {
    if (current == parent->left) {
        parent->left = child;
    } else {
        parent->right = child;
    }
}

static void splay(pNode *root, pNode pivot) {
    pNode aux = createNode(0, 0);
    pNode left = aux;
    pNode right = aux;

    pNode current = *root;
    while (pivot != current) {
        if (pivot->key < current->key) {
            if (pivot->key < current->left->key) {
                current = leftRotation(current);
            }
            right->left = current;
            right = current;
            current = current->left;
        } else {
            if (pivot->key > current->right->key) {
                current = rightRotation(current);
            }
            left->right = current;
            left = current;
            current = current->right;
        }
    }

    left->right = current->left;
    right->left = current->right;
    current->left = aux->right;
    current->right = aux->left;
    *root = current;
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
