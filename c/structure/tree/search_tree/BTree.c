#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    int *keys;
    int *values;
    struct node **children;
    int count;
    int leaf;
} TreeNode;

typedef TreeNode *pNode;

typedef struct {
    pNode root;
    int degree;
} BTreeNode;

static pNode createNode(int degree, int leaf);
static void addNode(pNode parent, int key, int value, int degree);
static void eraseNode(pNode parent, int key, int degree);
static void splitChild(pNode parent, pNode child, int index, int degree);
static void fillChild(pNode parent, int index, int degree);
static void mergeChild(pNode parent, int index, int degree);
static void borrowFromPrev(pNode parent, int index);
static void borrowFromNext(pNode parent, int index);

void create(BTreeNode *tree, int degree) {
    tree->root = NULL;
    tree->degree = degree;
}

int isEmpty(BTreeNode tree) {
    return !tree.root ? 1 : 0;
}

void add(BTreeNode *tree, int key, int value) {
    if (!tree->root) {
        tree->root = createNode(tree->degree, 1);
        tree->root->keys[0] = key;
        tree->root->values[0] = value;
        ++tree->root->count;
        return;
    }

    if (tree->root->count != (tree->degree << 1) - 1) {
        addNode(tree->root, key, value, tree->degree);
        return;
    }

    pNode node = createNode(tree->degree, 0);
    node->children[0] = tree->root;
    splitChild(node, tree->root, 0, tree->degree);

    int index = (node->keys[0] < key) ? 1 : 0;
    addNode(node->children[index], key, value, tree->degree);
    tree->root = node;
}

void erase(BTreeNode *tree, int key) {
    if (!tree->root) {
        return;
    }

    eraseNode(tree->root, key, tree->degree);
    if (!tree->root->count) {
        tree->root = tree->root->leaf ? NULL : tree->root->children[0];
    }
}

void set(BTreeNode *tree, int key, int value) {
    pNode current = tree->root;
    while (current) {
        int start = 0;
        int end = current->count - 1;
        while (start <= end) {
            int middle = start + ((end - start) >> 1);
            if (key == current->keys[middle]) {
                current->values[middle] = value;
                return;
            }

            if (key < current->keys[middle]) {
                end = middle - 1;
            } else {
                start = middle + 1;
            }
        }

        if (current->leaf) {
            return;
        }
        current = current->children[start];
    }
}

int get(BTreeNode tree, int key) {
    pNode current = tree.root;
    while (current) {
        int start = 0;
        int end = current->count - 1;
        while (start <= end) {
            int middle = start + ((end - start) >> 1);
            if (key == current->keys[middle]) {
                return current->values[middle];
            }

            if (key < current->keys[middle]) {
                end = middle - 1;
            } else {
                start = middle + 1;
            }
        }

        if (current->leaf) {
            return 1 << 31;
        }
        current = current->children[start];
    }
    return 1 << 31;
}

void clear(BTreeNode *tree) {
    tree->root = NULL;
}

static pNode createNode(int degree, int leaf) {
    pNode node = (pNode) malloc(sizeof(TreeNode));
    node->keys = (int *) malloc(sizeof(int) * ((degree << 1) - 1));
    memset(node->keys, 0, sizeof(int) * ((degree << 1) - 1));
    node->values = (int *) malloc(sizeof(int) * ((degree << 1) - 1));
    memset(node->values, 0, sizeof(int) * ((degree << 1) - 1));
    if (!leaf) {
        node->children = (pNode *) malloc(sizeof(pNode) * (degree << 1));
        for (int i = 0; i < (degree << 1); ++i) {
            node->children[i] = NULL;
        }
    }
    node->count = 0;
    node->leaf = leaf;
    return node;
}

static void addNode(pNode parent, int key, int value, int degree) {
    int start = 0;
    int end = parent->count - 1;
    while (start <= end) {
        int middle = start + ((end - start) >> 1);
        if (key == parent->keys[middle]) {
            parent->values[middle] = value;
            return;
        }

        if (key < parent->keys[middle]) {
            end = middle - 1;
        } else {
            start = middle + 1;
        }
    }

    if (parent->leaf) {
        for (int i = parent->count - 1; i > end; --i) {
            parent->keys[i + 1] = parent->keys[i];
            parent->values[i + 1] = parent->values[i];
        }
        parent->keys[end + 1] = key;
        parent->values[end + 1] = value;
        ++parent->count;
        return;
    }

    if (parent->children[end + 1]->count == (degree << 1) - 1) {
        splitChild(parent, parent->children[end + 1], end + 1, degree);
        if (parent->keys[end + 1] < key) {
            ++end;
        }
    }
    addNode(parent->children[end + 1], key, value, degree);
}

static void eraseNode(pNode parent, int key, int degree) {
    int start = 0;
    int end = parent->count - 1;
    int exists = 0;
    while (start <= end) {
        int middle = start + ((end - start) >> 1);
        if (key == parent->keys[middle]) {
            exists = 1;
            break;
        }

        if (key < parent->keys[middle]) {
            end = middle - 1;
        } else {
            start = middle + 1;
        }
    }

    if (!exists) {
        if (parent->leaf) {
            return;
        }

        int flag = (start == parent->count) ? 1 : 0;
        if (parent->children[start]->count < degree) {
            fillChild(parent, start, degree);
        }

        if (flag && start > parent->count) {
            eraseNode(parent->children[start - 1], key, degree);
        } else {
            eraseNode(parent->children[start], key, degree);
        }
        return;
    }

    if (parent->leaf) {
        for (int i = start + 1; i < parent->count; ++i) {
            parent->keys[i - 1] = parent->keys[i];
            parent->values[i - 1] = parent->values[i];
        }
        --parent->count;
        return;
    }

    if (parent->children[start]->count >= degree) {
        pNode current = parent->children[start];
        while (!current->leaf) {
            current = current->children[current->count];
        }

        parent->keys[start] = current->keys[current->count - 1];
        parent->values[start] = current->values[current->count - 1];
        eraseNode(parent->children[start], current->keys[current->count - 1], degree);
        return;
    }

    if (parent->children[start + 1]->count >= degree) {
        pNode current = parent->children[start + 1];
        while (!current->leaf) {
            current = current->children[0];
        }

        parent->keys[start] = current->keys[0];
        parent->values[start] = current->values[0];
        eraseNode(parent->children[start + 1], current->keys[0], degree);
        return;
    }

    mergeChild(parent, start, degree);
    eraseNode(parent->children[start], key, degree);
}

static void splitChild(pNode parent, pNode child, int index, int degree) {
    pNode node = createNode(degree, child->leaf);
    memcpy(node->keys, child->keys + degree, sizeof(int) * (child->count - degree));
    memcpy(node->values, child->values + degree, sizeof(int) * (child->count - degree));
    if (!child->leaf) {
        for (int i = degree; i < child->count + 1; ++i) {
            node->children[i - degree] = child->children[i];
        }
    }

    for (int i = parent->count - 1; i >= index; --i) {
        parent->keys[i + 1] = parent->keys[i];
        parent->values[i + 1] = parent->values[i];
    }
    for (int i = parent->count; i > index; --i) {
        parent->children[i + 1] = parent->children[i];
    }
    parent->keys[index] = child->keys[degree - 1];
    parent->values[index] = child->values[degree - 1];
    parent->children[index + 1] = node;

    node->count = degree - 1;
    child->count = degree - 1;
    ++parent->count;
}

static void fillChild(pNode parent, int index, int degree) {
    if (index && parent->children[index - 1]->count >= degree) {
        borrowFromPrev(parent, index);
        return;
    }

    if (index != parent->count && parent->children[index + 1]->count >= degree) {
        borrowFromNext(parent, index);
        return;
    }

    if (index != parent->count) {
        mergeChild(parent, index, degree);
    } else {
        mergeChild(parent, index - 1, degree);
    }
}

static void mergeChild(pNode parent, int index, int degree) {
    pNode child = parent->children[index];
    pNode node = parent->children[index + 1];

    child->keys[degree - 1] = parent->keys[index];
    child->values[degree - 1] = parent->values[index];
    memcpy(child->keys + degree, node->keys, sizeof(int) * child->count);
    memcpy(child->values + degree, node->values, sizeof(int) * child->count);
    if (!child->leaf) {
        for (int i = 0; i < child->count + 1; ++i) {
            child->children[i + degree] = node->children[i];
        }
    }

    for (int i = index + 1; i < parent->count; ++i) {
        parent->keys[i - 1] = parent->keys[i];
        parent->values[i - 1] = parent->values[i];
    }
    for (int i = index + 2; i <= parent->count; ++i) {
        parent->children[i - 1] = parent->children[i];
    }

    child->count += node->count + 1;
    --parent->count;
}

static void borrowFromPrev(pNode parent, int index) {
    pNode child = parent->children[index];
    pNode node = parent->children[index - 1];

    for (int i = child->count - 1; i >= 0; --i) {
        child->keys[i + 1] = child->keys[i];
        child->values[i + 1] = child->values[i];
    }
    child->keys[0] = parent->keys[index - 1];
    child->values[0] = parent->values[index - 1];
    if (!child->leaf) {
        for (int i = child->count; i >= 0; --i) {
            child->children[i + 1] = child->children[i];
        }
        child->children[0] = node->children[node->count];
    }

    parent->keys[index - 1] = node->keys[node->count - 1];
    parent->values[index - 1] = node->values[node->count - 1];

    ++child->count;
    --node->count;
}

static void borrowFromNext(pNode parent, int index) {
    pNode child = parent->children[index];
    pNode node = parent->children[index + 1];

    child->keys[child->count] = parent->keys[index];
    child->values[child->count] = parent->values[index];
    if (!child->leaf) {
        child->children[child->count + 1] = node->children[0];
    }

    parent->keys[index] = node->keys[0];
    parent->values[index] = node->values[0];

    for (int i = 1; i < node->count; ++i) {
        node->keys[i - 1] = node->keys[i];
        node->values[i - 1] = node->values[i];
    }
    if (!node->leaf) {
        for (int i = 1; i <= node->count; ++i) {
            node->children[i - 1] = node->children[i];
        }
    }

    ++child->count;
    --node->count;
}
