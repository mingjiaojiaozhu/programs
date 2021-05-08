#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct node {
    int value;
    int degree;
    struct node *child;
    struct node *parent;
    struct node *left;
    struct node *right;
    int marked;
} TreeNode;

typedef TreeNode *pNode;

typedef struct {
    pNode root;
    int length;
} HeapNode;

static pNode createNode(int value);
static void combine(HeapNode *heap);
static pNode search(pNode node, int value);
static void increase(HeapNode *heap, pNode node);
static void decrease(HeapNode *heap, pNode node);
static void link(pNode parent, pNode child);
static void addNode(pNode node1, pNode node2);
static void eraseNode(pNode node);
static void cut(HeapNode *heap, pNode node, pNode parent);
static void cascadingCut(HeapNode *heap, pNode node);
static void setDegree(pNode parent, int degree);

void create(HeapNode *heap) {
    heap->root = NULL;
    heap->length = 0;
}

int isEmpty(HeapNode heap) {
    return !heap.root ? 1 : 0;
}

void add(HeapNode *heap, int value) {
    if (search(heap->root, value)) {
        return;
    }

    if (!heap->root) {
        heap->root = createNode(value);
        heap->root->left = heap->root;
        heap->root->right = heap->root;
    } else {
        pNode node = createNode(value);
        addNode(node, heap->root);
        if (value < heap->root->value) {
            heap->root = node;
        }
    }
    ++heap->length;
}

void erase(HeapNode *heap, int value) {
    pNode node = search(heap->root, value);
    if (!node) {
        return;
    }

    if (value != heap->root->value) {
        node->value = heap->root->value - 1;
        decrease(heap, node);
    }

    pNode current = heap->root;
    while (current->child) {
        pNode child = current->child;
        eraseNode(child);
        current->child = (child->right != child) ? child->right : NULL;
        addNode(child, heap->root);
        child->parent = NULL;
    }

    eraseNode(current);
    heap->root = (current->right != current) ? current->right : NULL;
    if (current->right != current) {
        combine(heap);
    }
    --heap->length;
}

void set(HeapNode *heap, int target, int value) {
    pNode node = search(heap->root, target);
    if (node && target != value && !search(heap->root, value)) {
        node->value = value;
        if (target < value) {
            increase(heap, node);
        } else {
            decrease(heap, node);
        }
    }
}

int getRoot(HeapNode heap) {
    if (heap.root) {
        return heap.root->value;
    }
    return 1 << 31;
}

int contains(HeapNode heap, int value) {
    return search(heap.root, value) ? 1 : 0;
}

void clear(HeapNode *heap) {
    heap->root = NULL;
    heap->length = 0;
}

static pNode createNode(int value) {
    pNode node = (pNode) malloc(sizeof(TreeNode));
    node->value = value;
    node->degree = 0;
    node->child = NULL;
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;
    node->marked = 0;
    return node;
}

static void combine(HeapNode *heap) {
    int maxDegree = (int) ceil(log((double) heap->length) / log((double) 2));
    pNode *heads = (pNode *) malloc(sizeof(pNode) * (maxDegree + 1));
    for (int i = 0; i <= maxDegree; ++i) {
        heads[i] = NULL;
    }

    while (heap->root) {
        pNode current = heap->root;
        if (current == current->right) {
            heap->root = NULL;
        } else {
            eraseNode(current);
            heap->root = current->right;
        }
        current->left = current;
        current->right = current;

        int degree = current->degree;
        while (heads[degree]) {
            pNode node = heads[degree];
            if (current->value > node->value) {
                pNode aux = current;
                current = node;
                node = aux;
            }

            link(node, current);
            heads[degree] = NULL;
            ++degree;
        }
        heads[degree] = current;
    }

    for (int i = 0; i <= maxDegree; ++i) {
        pNode head = heads[i];
        if (!head) {
            continue;
        }

        if (!heap->root) {
            heap->root = head;
        } else {
            addNode(head, heap->root);
            if (head->value < heap->root->value) {
                heap->root = head;
            }
        }
    }
}

static pNode search(pNode node, int value) {
    if (!node) {
        return NULL;
    }

    pNode current = node;
    int flag = 1;
    while (flag || current != node) {
        flag = 0;
        if (current->value == value) {
            return current;
        }

        pNode child = search(current->child, value);
        if (child) {
            return child;
        }
        current = current->right;
    }
    return NULL;
}

static void increase(HeapNode *heap, pNode node) {
    while (node->child) {
        pNode child = node->child;
        eraseNode(child);
        if (child->right == child) {
            node->child = NULL;
        } else {
            node->child = child->right;
        }

        addNode(child, heap->root);
        child->parent = NULL;
    }
    node->degree = 0;

    pNode parent = node->parent;
    if (parent) {
        cut(heap, node, parent);
        cascadingCut(heap, parent);
    } else if (heap->root == node) {
        pNode right = node->right;
        while (right != node) {
            if (node->value > right->value) {
                heap->root = right;
            }
            right = right->right;
        }
    }
}

static void decrease(HeapNode *heap, pNode node) {
    pNode parent = node->parent;
    if (parent && node->value < parent->value) {
        cut(heap, node, parent);
        cascadingCut(heap, parent);
    }

    if (node->value < heap->root->value) {
        heap->root = node;
    }
}

static void link(pNode parent, pNode child) {
    eraseNode(parent);
    if (!child->child) {
        child->child = parent;
    } else {
        addNode(parent, child->child);
    }

    parent->parent = child;
    parent->marked = 0;
    ++child->degree;
}

static void addNode(pNode node1, pNode node2) {
    node2->left->right = node1;
    node1->left = node2->left;
    node1->right = node2;
    node2->left = node1;
}

static void eraseNode(pNode node) {
    node->left->right = node->right;
    node->right->left = node->left;
}

static void cut(HeapNode *heap, pNode node, pNode parent) {
    eraseNode(node);
    setDegree(parent, node->degree);
    parent->child = (node != node->right) ? node->right : NULL;

    node->parent = NULL;
    node->left = node;
    node->right = node;
    node->marked = 0;
    addNode(node, heap->root);
}

static void cascadingCut(HeapNode *heap, pNode node) {
    pNode parent = node->parent;
    if (parent) {
        if (!node->marked) {
            node->marked = 1;
        } else {
            cut(heap, node, parent);
            cascadingCut(heap, parent);
        }
    }
}

static void setDegree(pNode parent, int degree) {
    parent->degree -= degree;
    if (parent->parent) {
        setDegree(parent->parent, degree);
    }
}
