#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int key;
    int value;
    char color;
    struct node *left;
    struct node *right;
    struct node *parent;
} TreeNode;

typedef TreeNode *pNode;

static const char red = '0';
static const char black = '1';

static pNode createNode(int key, int value, char color, pNode parent);
static void addNode(pNode *root, pNode parent, int key, int value);
static void eraseNode(pNode *root, pNode parent, pNode current, pNode child);
static void addFixup(pNode *root, pNode current);
static void eraseFixup(pNode *root, pNode current, pNode parent);
static pNode addFixupNode(pNode *root, pNode current, pNode parent, pNode grandParent, pNode uncle, pNode brother, int isLeft);
static pNode eraseFixupNode(pNode *root, pNode parent, pNode brother, int isLeft);
static void leftRotation(pNode *root, pNode current);
static void rightRotation(pNode *root, pNode current);

int isEmpty(pNode root) {
    return !root ? 1 : 0;
}

void add(pNode *root, int key, int value) {
    if (!*root) {
        *root = createNode(key, value, black, NULL);
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
    addNode(root, parent, key, value);
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
        eraseNode(root, parent, current, current->left ? current->left : current->right);
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
    eraseNode(root, parent, child, child->right);
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

static pNode createNode(int key, int value, char color, pNode parent) {
    pNode node = (pNode) malloc(sizeof(TreeNode));
    node->key = key;
    node->value = value;
    node->color = color;
    node->left = NULL;
    node->right = NULL;
    node->parent = parent;
    return node;
}

static void addNode(pNode *root, pNode parent, int key, int value) {
    pNode child = createNode(key, value, red, parent);
    if (key < parent->key) {
        parent->left = child;
    } else {
        parent->right = child;
    }
    addFixup(root, child);
}

static void eraseNode(pNode *root, pNode parent, pNode current, pNode child) {
    char color = current->color;
    if (current == parent->left) {
        parent->left = child;
    } else {
        parent->right = child;
    }

    if (child) {
        child->parent = parent;
    }

    if (black == color) {
        eraseFixup(root, child, parent);
    }
}

static void addFixup(pNode *root, pNode current) {
    pNode parent = current->parent;
    while (parent && red == parent->color) {
        pNode grandParent = parent->parent;
        if (parent == grandParent->left) {
            current = addFixupNode(root, current, parent, grandParent, grandParent->right, parent->right, 1);
        } else {
            current = addFixupNode(root, current, parent, grandParent, grandParent->left, parent->left, 0);
        }
        parent = current->parent;
    }
    (*root)->color = black;
}

static void eraseFixup(pNode *root, pNode current, pNode parent) {
    while ((!current || black == current->color) && current != *root) {
        if (parent->left == current) {
            current = eraseFixupNode(root, parent, parent->right, 1);
        } else {
            current = eraseFixupNode(root, parent, parent->left, 0);
        }
        parent = current->parent;
    }

    if (current) {
        current->color = black;
    }
}

static pNode addFixupNode(pNode *root, pNode current, pNode parent, pNode grandParent, pNode uncle, pNode brother, int isLeft) {
    if (uncle && red == uncle->color) {
        uncle->color = black;
        parent->color = black;
        grandParent->color = red;
        return grandParent;
    }

    if (brother == current) {
        if (isLeft) {
            leftRotation(root, parent);
        } else {
            rightRotation(root, parent);
        }

        pNode aux = parent;
        parent = current;
        current = aux;
    }

    parent->color = black;
    grandParent->color = red;
    if (isLeft) {
        rightRotation(root, grandParent);
    } else {
        leftRotation(root, grandParent);
    }
    return current;
}

static pNode eraseFixupNode(pNode *root, pNode parent, pNode brother, int isLeft) {
    if (red == brother->color) {
        brother->color = black;
        parent->color = red;

        if (isLeft) {
            leftRotation(root, parent);
            brother = parent->right;
        } else {
            rightRotation(root, parent);
            brother = parent->left;
        }
    }

    if ((!brother->left || black == brother->left->color) && (!brother->right || black == brother->right->color)) {
        brother->color = red;
        return parent;
    }

    if (isLeft && (!brother->right || black == brother->right->color)) {
        brother->left->color = black;
        brother->color = red;
        rightRotation(root, brother);
        brother = parent->right;
    }
    if (!isLeft && (!brother->left || black == brother->left->color)) {
        brother->right->color = black;
        brother->color = red;
        leftRotation(root, brother);
        brother = parent->left;
    }

    brother->color = parent->color;
    parent->color = black;
    if (isLeft) {
        brother->right->color = black;
        leftRotation(root, parent);
    } else {
        brother->left->color = black;
        rightRotation(root, parent);
    }
    return *root;
}

static void leftRotation(pNode *root, pNode current) {
    pNode child = current->right;
    current->right = child->left;
    if (child->left) {
        child->left->parent = current;
    }
    child->parent = current->parent;

    if (!current->parent) {
        *root = child;
    } else {
        if (current->parent->left == current) {
            current->parent->left = child;
        } else {
            current->parent->right = child;
        }
    }
    child->left = current;
    current->parent = child;
}

static void rightRotation(pNode *root, pNode current) {
    pNode child = current->left;
    current->left = child->right;
    if (child->right) {
        child->right->parent = current;
    }
    child->parent = current->parent;

    if (!current->parent) {
        *root = child;
    } else {
        if (current->parent->left == current) {
            current->parent->left = child;
        } else {
            current->parent->right = child;
        }
    }
    child->right = current;
    current->parent = child;
}
