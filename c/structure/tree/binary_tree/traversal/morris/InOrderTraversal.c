#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    int value;
    struct node *left;
    struct node *right;
} TreeNode;

typedef TreeNode *pNode;

typedef struct {
    int *values;
    int length;
    int capacity;
} ArrayNode;

void inOrderTraversal(pNode root, ArrayNode *result) {
    result->values = (int *) malloc(sizeof(int) * 64);
    memset(result->values, 0, sizeof(int) * 64);
    result->length = 0;
    result->capacity = 64;

    pNode current = root;
    while (current) {
        if (!current->left) {
            if (result->length >= result->capacity) {
                result->values = (int *) realloc(result->values, sizeof(int) * (result->capacity + 16));
                memset(result->values + result->capacity, 0, sizeof(int) * 16);
                result->capacity += 16;
            }
            result->values[result->length] = current->value;
            ++result->length;

            current = current->right;
            continue;
        }

        pNode aux = current->left;
        while (aux->right && aux->right != current) {
            aux = aux->right;
        }
        if (!aux->right) {
            aux->right = current;
            current = current->left;
        } else {
            if (result->length >= result->capacity) {
                result->values = (int *) realloc(result->values, sizeof(int) * (result->capacity + 16));
                memset(result->values + result->capacity, 0, sizeof(int) * 16);
                result->capacity += 16;
            }
            result->values[result->length] = current->value;
            ++result->length;

            aux->right = NULL;
            current = current->right;
        }
    }
}
