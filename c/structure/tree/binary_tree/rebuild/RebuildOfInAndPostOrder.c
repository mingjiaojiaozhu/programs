#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node *left;
    struct node *right;
} TreeNode;

typedef TreeNode *pNode;

pNode rebuildOfInAndPostOrder(int *inOrder, int *postOrder, int length) {
    int pivot = postOrder[length - 1];
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
        parent->left = rebuildOfInAndPostOrder(inOrder, postOrder, index);
    }
    if (index < length - 1) {
        parent->right = rebuildOfInAndPostOrder(inOrder + index + 1, postOrder + index, length - 1 - index);
    }
    return parent;
}
