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

typedef struct stack {
    pNode value;
    struct stack *next;
} StackNode;

static StackNode *createStack();
static void pushStack(StackNode *stack, pNode value);
static pNode popStack(StackNode *stack);

void postOrderTraversal(pNode root, ArrayNode *result) {
    result->values = (int *) malloc(sizeof(int) * 64);
    memset(result->values, 0, sizeof(int) * 64);
    result->length = 0;
    result->capacity = 64;

    StackNode *stack = createStack();
    pushStack(stack, root);
    pNode current = NULL;
    while (stack->next) {
        pNode aux = stack->next->value;
        if (aux->left && current != aux->left && current != aux->right) {
            pushStack(stack, aux->left);
        } else if (aux->right && current != aux->right) {
            pushStack(stack, aux->right);
        } else {
            if (result->length >= result->capacity) {
                result->values = (int *) realloc(result->values, sizeof(int) * (result->capacity + 16));
                memset(result->values + result->capacity, 0, sizeof(int) * 16);
                result->capacity += 16;
            }
            result->values[result->length] = aux->value;
            ++result->length;

            current = aux;
            popStack(stack);
        }
    }
}

static StackNode *createStack() {
    StackNode *stack = (StackNode *) malloc(sizeof(StackNode));
    stack->value = NULL;
    stack->next = NULL;
    return stack;
}

static void pushStack(StackNode *stack, pNode value) {
    StackNode *node = (StackNode *) malloc(sizeof(StackNode));
    node->value = value;
    node->next = stack->next;
    stack->next = node;
}

static pNode popStack(StackNode *stack) {
    StackNode *node = stack->next;
    stack->next = node->next;
    return node->value;
}
