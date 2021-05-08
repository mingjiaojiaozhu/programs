#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **values;
    int length;
} ArrayNode;

typedef struct textNode {
    char *value;
    struct textNode *next;
} StackTextNode;

typedef struct numNode {
    int value;
    struct numNode *next;
} StackNumNode;

static StackTextNode *createStackText();
static void pushStackText(StackTextNode *stack, char *value);
static char *popStackText(StackTextNode *stack);
static StackNumNode *createStackNum();
static void pushStackNum(StackNumNode *stack, int value);
static int popStackNum(StackNumNode *stack);

void converse(char **values, int length, ArrayNode *result) {
    StackTextNode *stack = createStackText();
    result->values = (char **) malloc(sizeof(char *) * length);
    for (int i = 0; i < length; ++i) {
        result->values[i] = NULL;
    }
    result->length = 0;
    for (int i = 0; i < length; ++i) {
        char *value = values[i];
        if (!memcmp(value, "(", sizeof(char))) {
            pushStackText(stack, value);
            continue;
        }

        if (!memcmp(value, ")", sizeof(char))) {
            while (stack->next) {
                char *sign = popStackText(stack);
                if (!memcmp(sign, "(", sizeof(char))) {
                    break;
                }
                result->values[result->length] = sign;
                ++result->length;
            }
            continue;
        }

        if (memcmp(value, "+", sizeof(char)) && memcmp(value, "-", sizeof(char)) && memcmp(value, "*", sizeof(char)) && memcmp(value, "/", sizeof(char))) {
            result->values[result->length] = value;
            ++result->length;
            continue;
        }

        while (stack->next) {
            char *sign = stack->next->value;
            if (!memcmp(sign, "(", sizeof(char)) || ((!memcmp(value, "*", sizeof(char)) || !memcmp(value, "/", sizeof(char)) && (!memcmp(sign, "+", sizeof(char)) || !memcmp(sign, "-", sizeof(char)))))) {
                break;
            }
            result->values[result->length] = sign;
            ++result->length;
            popStackText(stack);
        }
        pushStackText(stack, value);
    }

    while (stack->next) {
        result->values[result->length] = popStackText(stack);
        ++result->length;
    }
}

int evaluate(char **values, int length) {
    StackNumNode *stack = createStackNum();
    for (int i = 0; i < length; ++i) {
        char *value = values[i];
        if (memcmp(value, "+", sizeof(char)) && memcmp(value, "-", sizeof(char)) && memcmp(value, "*", sizeof(char)) && memcmp(value, "/", sizeof(char))) {
            pushStackNum(stack, atoi(value));
            continue;
        }

        int num1 = popStackNum(stack);
        int num2 = popStackNum(stack);
        if (!memcmp(value, "+", sizeof(char))) {
            pushStackNum(stack, num2 + num1);
        } else if (!memcmp(value, "-", sizeof(char))) {
            pushStackNum(stack, num2 - num1);
        } else if (!memcmp(value, "*", sizeof(char))) {
            pushStackNum(stack, num2 * num1);
        } else {
            pushStackNum(stack, num2 / num1);
        }
    }
    return stack->next->value;
}

static StackTextNode *createStackText() {
    StackTextNode *stack = (StackTextNode *) malloc(sizeof(StackTextNode));
    stack->value = "";
    stack->next = NULL;
    return stack;
}

static void pushStackText(StackTextNode *stack, char *value) {
    StackTextNode *node = (StackTextNode *) malloc(sizeof(StackTextNode));
    node->value = value;
    node->next = stack->next;
    stack->next = node;
}

static char *popStackText(StackTextNode *stack) {
    StackTextNode *node = stack->next;
    stack->next = node->next;
    return node->value;
}

static StackNumNode *createStackNum() {
    StackNumNode *stack = (StackNumNode *) malloc(sizeof(StackNumNode));
    stack->value = 0;
    stack->next = NULL;
    return stack;
}

static void pushStackNum(StackNumNode *stack, int value) {
    StackNumNode *node = (StackNumNode *) malloc(sizeof(StackNumNode));
    node->value = value;
    node->next = stack->next;
    stack->next = node;
}

static int popStackNum(StackNumNode *stack) {
    StackNumNode *node = stack->next;
    stack->next = node->next;
    return node->value;
}
