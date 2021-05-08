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

void inOrderTraversal(pNode root, ArrayNode *result) {
    result->values = (int *) malloc(sizeof(int) * 64);
    memset(result->values, 0, sizeof(int) * 64);
    result->length = 0;
    result->capacity = 64;

    StackNode *stack = createStack();
    pNode current = root;
    while (current || stack->next) {
        while (current) {
            pushStack(stack, current);
            current = current->left;
        }

        current = popStack(stack);
        if (result->length >= result->capacity) {
            result->values = (int *) realloc(result->values, sizeof(int) * (result->capacity + 16));
            memset(result->values + result->capacity, 0, sizeof(int) * 16);
            result->capacity += 16;
        }
        result->values[result->length] = current->value;
        ++result->length;

        current = current->right;
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
