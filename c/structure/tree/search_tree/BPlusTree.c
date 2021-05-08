#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    int *keys;
    int *values;
    struct node **children;
    int count;
    int leaf;
    struct node *next;
} TreeNode;

typedef TreeNode *pNode;

typedef struct {
    pNode root;
    int degree;
} BPlusTreeNode;

static pNode createNode(int degree, int leaf);
static void addNode(pNode parent, int key, int value, int degree);
static void eraseNode(pNode parent, int key, int degree);
static void splitChild(pNode parent, pNode child, int index, int degree);
static void fillChild(pNode parent, int index, int degree);
static void mergeChild(pNode parent, int index, int degree);
static void borrowFromPrev(pNode parent, int index);
static void borrowFromNext(pNode parent, int index);

void create(BPlusTreeNode *tree, int degree) {
    tree->root = NULL;
    tree->degree = degree;
}

int isEmpty(BPlusTreeNode tree) {
    return !tree.root ? 1 : 0;
}

void add(BPlusTreeNode *tree, int key, int value) {
    if (!tree->root) {
        tree->root = createNode(tree->degree, 1);
        tree->root->keys[0] = key;
        tree->root->values[0] = value;
        return;
    }

    if (tree->root->count != (tree->degree << 1)) {
        addNode(tree->root, key, value, tree->degree);
        return;
    }

    pNode node = createNode(tree->degree, 0);
    node->children[0] = tree->root;
    splitChild(node, tree->root, 0, tree->degree);

    if (key > node->keys[node->count - 1]) {
        node->keys[node->count - 1] = key;
    }

    int index = (node->keys[0] < key) ? 1 : 0;
    addNode(node->children[index], key, value, tree->degree);
    tree->root = node;
}

void erase(BPlusTreeNode *tree, int key) {
    if (!tree->root) {
        return;
    }

    eraseNode(tree->root, key, tree->degree);
    if (!tree->root->count) {
        tree->root = NULL;
    } else if (tree->root->count <= 1 && !tree->root->leaf) {
        tree->root = tree->root->children[0];
    }
}

void set(BPlusTreeNode *tree, int key, int value) {
    pNode current = tree->root;
    while (current) {
        int start = 0;
        int end = current->count - 1;
        while (start <= end) {
            int middle = start + ((end - start) >> 1);
            if (key > current->keys[middle]) {
                start = middle + 1;
            } else {
                end = middle - 1;
            }
        }

        if (current->leaf) {
            if (start < current->count && key == current->keys[start]) {
                current->values[start] = value;
            }
            return;
        }

        if (start >= current->count) {
            return;
        }
        current = current->children[start];
    }
}

int get(BPlusTreeNode tree, int key) {
    pNode current = tree.root;
    while (current) {
        int start = 0;
        int end = current->count - 1;
        while (start <= end) {
            int middle = start + ((end - start) >> 1);
            if (key > current->keys[middle]) {
                start = middle + 1;
            } else {
                end = middle - 1;
            }
        }

        if (current->leaf) {
            if (start < current->count && key == current->keys[start]) {
                return current->values[start];
            }
            return 1 << 31;
        }

        if (start >= current->count) {
            return 1 << 31;
        }
        current = current->children[start];
    }
    return 1 << 31;
}

void clear(BPlusTreeNode *tree) {
    tree->root = NULL;
}

static pNode createNode(int degree, int leaf) {
    pNode node = (pNode) malloc(sizeof(TreeNode));
    node->keys = (int *) malloc(sizeof(int) * (degree << 1));
    memset(node->keys, 0, sizeof(int) * (degree << 1));
    if (leaf) {
        node->values = (int *) malloc(sizeof(int) * (degree << 1));
        memset(node->values, 0, sizeof(int) * (degree << 1));
    } else {
        node->children = (pNode *) malloc(sizeof(pNode) * (degree << 1));
        for (int i = 0; i < (degree << 1); ++i) {
            node->children[i] = NULL;
        }
    }
    node->count = 1;
    node->leaf = leaf;
    node->next = NULL;
    return node;
}

static void addNode(pNode parent, int key, int value, int degree) {
    int start = 0;
    int end = parent->count - 1;
    while (start <= end) {
        int middle = start + ((end - start) >> 1);
        if (key > parent->keys[middle]) {
            start = middle + 1;
        } else {
            end = middle - 1;
        }
    }

    if (parent->leaf) {
        if (start < parent->count && key == parent->keys[start]) {
            parent->values[start] = value;
            return;
        }

        for (int i = parent->count - 1; i >= start; --i) {
            parent->keys[i + 1] = parent->keys[i];
            parent->values[i + 1] = parent->values[i];
        }
        parent->keys[start] = key;
        parent->values[start] = value;
        ++parent->count;
        return;
    }

    if (start >= parent->count) {
        start = parent->count - 1;
    }

    if (parent->children[start]->count == (degree << 1)) {
        splitChild(parent, parent->children[start], start, degree);
        if (parent->keys[start] < key) {
            ++start;
        }
    }

    if (key > parent->keys[parent->count - 1]) {
        parent->keys[parent->count - 1] = key;
    }
    addNode(parent->children[start], key, value, degree);
}

static void eraseNode(pNode parent, int key, int degree) {
    int start = 0;
    int end = parent->count - 1;
    while (start <= end) {
        int middle = start + ((end - start) >> 1);
        if (key > parent->keys[middle]) {
            start = middle + 1;
        } else {
            end = middle - 1;
        }
    }

    if (parent->leaf) {
        if (key != parent->keys[start]) {
            return;
        }

        for (int i = start + 1; i < parent->count; ++i) {
            parent->keys[i - 1] = parent->keys[i];
            parent->values[i - 1] = parent->values[i];
        }
        --parent->count;
        return;
    }

    int flag = (start == parent->count - 1) ? 1 : 0;
    if (parent->children[start]->count <= degree) {
        fillChild(parent, start, degree);
    }

    if (flag && start > parent->count - 1) {
        eraseNode(parent->children[start - 1], key, degree);
    } else {
        eraseNode(parent->children[start], key, degree);
    }

    if (key == parent->keys[parent->count - 1]) {
        parent->keys[parent->count - 1] = parent->children[parent->count - 1]->keys[parent->children[parent->count - 1]->count - 1];
    }
}

static void splitChild(pNode parent, pNode child, int index, int degree) {
    pNode node = createNode(degree, child->leaf);
    memcpy(node->keys, child->keys + degree, sizeof(int) * (child->count - degree));
    if (child->leaf) {
        memcpy(node->values, child->values + degree, sizeof(int) * (child->count - degree));

        node->next = child->next;
        child->next = node;
    } else {
        for (int i = degree; i < child->count; ++i) {
            node->children[i - degree] = child->children[i];
        }
    }

    for (int i = parent->count - 1; i > index; --i) {
        parent->keys[i + 1] = parent->keys[i];
        parent->children[i + 1] = parent->children[i];
    }
    parent->keys[index] = child->keys[degree - 1];
    parent->keys[index + 1] = node->keys[degree - 1];
    parent->children[index + 1] = node;

    node->count = degree;
    child->count = degree;
    ++parent->count;
}

static void fillChild(pNode parent, int index, int degree) {
    if (index && parent->children[index - 1]->count > degree) {
        borrowFromPrev(parent, index);
        return;
    }

    if (index != parent->count - 1 && parent->children[index + 1]->count > degree) {
        borrowFromNext(parent, index);
        return;
    }

    if (index != parent->count - 1) {
        mergeChild(parent, index, degree);
    } else {
        mergeChild(parent, index - 1, degree);
    }
}

static void mergeChild(pNode parent, int index, int degree) {
    pNode child = parent->children[index];
    pNode node = parent->children[index + 1];

    memcpy(child->keys + degree, node->keys, sizeof(int) * node->count);
    if (child->leaf) {
        memcpy(child->values + degree, node->values, sizeof(int) * node->count);
        child->next = node->next;
    } else {
        for (int i = 0; i < node->count; ++i) {
            child->children[i + degree] = node->children[i];
        }
    }

    parent->keys[index] = node->keys[node->count - 1];
    for (int i = index + 2; i < parent->count; ++i) {
        parent->keys[i - 1] = parent->keys[i];
        parent->children[i - 1] = parent->children[i];
    }

    child->count += node->count;
    --parent->count;
}

static void borrowFromPrev(pNode parent, int index) {
    pNode child = parent->children[index];
    pNode node = parent->children[index - 1];

    for (int i = child->count - 1; i >= 0; --i) {
        child->keys[i + 1] = child->keys[i];
    }
    child->keys[0] = node->keys[node->count - 1];
    if (child->leaf) {
        for (int i = child->count - 1; i >= 0; --i) {
            child->values[i + 1] = child->values[i];
        }
        child->values[0] = node->values[node->count - 1];
    } else {
        for (int i = child->count - 1; i >= 0; --i) {
            child->children[i + 1] = child->children[i];
        }
        child->children[0] = node->children[node->count - 1];
    }

    parent->keys[index - 1] = node->keys[node->count - 2];

    ++child->count;
    --node->count;
}

static void borrowFromNext(pNode parent, int index) {
    pNode child = parent->children[index];
    pNode node = parent->children[index + 1];

    child->keys[child->count] = node->keys[0];
    if (child->leaf) {
        child->values[child->count] = node->values[0];
    } else {
        child->children[child->count] = node->children[0];
    }

    for (int i = 1; i < node->count; ++i) {
        node->keys[i - 1] = node->keys[i];
    }
    if (node->leaf) {
        for (int i = 1; i < node->count; ++i) {
            node->values[i - 1] = node->values[i];
        }
    } else {
        for (int i = 1; i < node->count; ++i) {
            node->children[i - 1] = node->children[i];
        }
    }

    parent->keys[index] = child->keys[child->count];

    ++child->count;
    --node->count;
}
