#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node *left;
    struct node *right;
} TreeNode;

typedef TreeNode *pNode;

pNode rebuildOfPreAndInOrder(int *preOrder, int *inOrder, int length) {
    int pivot = preOrder[0];
    pNode parent = (pNode) malloc(sizeof(TreeNode));
    parent->value = pivot;
    parent->left = NULL;
    parent->right = NULL;
    if (1 == length) {
        return parent;
    }

    int index = 0;
    while (index < length && pivot != inOrder[index]) {
        ++index;
    }

    if (index > 0) {
        parent->left = rebuildOfPreAndInOrder(preOrder + 1, inOrder, index);
    }
    if (index < length - 1) {
        parent->right = rebuildOfPreAndInOrder(preOrder + index + 1, inOrder + index + 1, length - 1 - index);
    }
    return parent;
}
