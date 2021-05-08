#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    struct node **next;
    int depth;
    int ended;
} TreeNode;

typedef TreeNode *pNode;

static pNode createNode();
static pNode eraseNode(pNode current, char *text, int depth, int pos);

void create(pNode *root) {
    *root = createNode();
}

int isEmpty(pNode root) {
    for (int i = 0; i < 26; ++i) {
        if (root->next[i]) {
            return 0;
        }
    }
    return 1;
}

void add(pNode *root, char *text) {
    pNode current = *root;
    for (char *p = text; '\0' != *p; ++p) {
        int index = *p - 'a';
        if (!current->next[index]) {
            current->next[index] = createNode();
            ++current->depth;
        }
        current = current->next[index];
    }
    current->ended = 1;
}

void erase(pNode *root, char *text) {
    int index = text[0] - 'a';
    (*root)->next[index] = eraseNode((*root)->next[index], text, strlen(text), 1);
}

int contains(pNode root, char *text) {
    pNode current = root;
    for (char *p = text; '\0' != *p; ++p) {
        int index = *p - 'a';
        pNode next = current->next[index];
        if (!next) {
            return 0;
        }
        current = next;
    }
    return current->ended;
}

void clear(pNode *root) {
    for (int i = 0; i < 26; ++i) {
        (*root)->next[i] = NULL;
    }
}

static pNode createNode() {
    pNode node = (pNode) malloc(sizeof(TreeNode));
    node->next = (pNode *) malloc(sizeof(pNode) * 26);
    for (int i = 0; i < 26; ++i) {
        node->next[i] = NULL;
    }
    node->depth = 0;
    node->ended = 0;
    return node;
}

static pNode eraseNode(pNode current, char *text, int depth, int pos) {
    if (!current) {
        return NULL;
    }

    if (pos >= depth) {
        if (!current->depth) {
            return NULL;
        }
        current->ended = 0;
        return current;
    }

    int index = text[pos] - 'a';
    current->next[index] = eraseNode(current->next[index], text, depth, pos + 1);
    if (current->next[index]) {
        return current;
    }

    if (current->depth) {
        --current->depth;
    }
    if (!current->depth && !current->ended) {
        return NULL;
    }
    return current;
}
