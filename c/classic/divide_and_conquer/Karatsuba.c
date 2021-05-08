#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *values;
    int length;
} ArrayNode;

static char *multiply(char *num1, char *num2);
static char *add(char *num1, char *num2);
static char *subtract(char *num1, char *num2);
static char *fillHead(char *num, int length);
static char *fillTail(char *num, int length);
static ArrayNode *stringToArrays(char *num, int length);
static char *arraysToString(ArrayNode *values);
static ArrayNode *createArrays(int length);
static char *createString(int length);
static void reverse(ArrayNode *values);
static int max(int i, int j);

void karatsuba(char *num1, char *num2, char **result) {
    *result = multiply(num1, num2);
}

static char *multiply(char *num1, char *num2) {
    int length = max(strlen(num1), strlen(num2));
    if (length <= 4) {
        char *result = createString(length << 1);
        sprintf(result, "%d", atoi(num1) * atoi(num2));
        return result;
    }

    if (length > (int) strlen(num1)) {
        num1 = fillHead(num1, length - strlen(num1));
    }
    if (length > (int) strlen(num2)) {
        num2 = fillHead(num2, length - strlen(num2));
    }

    int halfSize = length >> 1;
    char *num1Head = createString(halfSize + 1);
    memcpy(num1Head, num1, sizeof(char) * halfSize);
    char *num1Tail = createString(halfSize + 1);
    memcpy(num1Tail, num1 + halfSize, sizeof(char) * (length - halfSize));
    char *num2Head = createString(halfSize + 1);
    memcpy(num2Head, num2, sizeof(char) * halfSize);
    char *num2Tail = createString(halfSize + 1);
    memcpy(num2Tail, num2 + halfSize, sizeof(char) * (length - halfSize));
    char *aux1 = multiply(num1Head, num2Head);
    char *aux2 = multiply(num1Tail, num2Tail);
    return add(add(fillTail(aux1, (length - halfSize) << 1), fillTail(subtract(multiply(add(num1Head, num1Tail), add(num2Head, num2Tail)), add(aux1, aux2)), length - halfSize)), aux2);
}

static char *add(char *num1, char *num2) {
    int length1 = strlen(num1);
    int length2 = strlen(num2);
    ArrayNode *values1 = stringToArrays(num1, length1);
    ArrayNode *values2 = stringToArrays(num2, length2);

    ArrayNode *result = createArrays(max(strlen(num1), strlen(num2)) + 1);
    memcpy(result->values, values1->values, sizeof(int) * values1->length);
    for (int i = 0; i < length2; ++i) {
        result->values[i] += values2->values[i];
        if (result->values[i] >= 10) {
            result->values[i] -= 10;
            ++result->values[i + 1];
        }
    }

    int index = length2;
    while (index < length1 - 1 && result->values[index] >= 10) {
        result->values[index] -= 10;
        ++result->values[index + 1];
        ++index;
    }
    return arraysToString(result);
}

static char *subtract(char *num1, char *num2) {
    int length1 = strlen(num1);
    int length2 = strlen(num2);
    ArrayNode *values1 = stringToArrays(num1, length1);
    ArrayNode *values2 = stringToArrays(num2, length2);
    for (int i = 0; i < length2; ++i) {
        values1->values[i] -= values2->values[i];
        if (values1->values[i] < 0) {
            values1->values[i] += 10;
            --values1->values[i + 1];
        }
    }

    int index = length2;
    while (index < length1 - 1 && values1->values[index] < 0) {
        values1->values[index] += 10;
        --values1->values[index + 1];
        ++index;
    }
    return arraysToString(values1);
}

static char *fillHead(char *num, int length) {
    char *result = createString(strlen(num) + length);
    memset(result, '0', sizeof(char) * length);
    memcpy(result + length, num, sizeof(char) * strlen(num));
    return result;
}

static char *fillTail(char *num, int length) {
    char *result = createString(strlen(num) + length);
    memcpy(result, num, sizeof(char) * strlen(num));
    memset(result + strlen(num), '0', sizeof(char) * length);
    return result;
}

static ArrayNode *stringToArrays(char *num, int length) {
    ArrayNode *result = createArrays(length);
    int index = 0;
    for (char *p = num; '\0' != *p; ++p) {
        result->values[index] = *p - '0';
        ++index;
    }
    reverse(result);
    return result;
}

static char *arraysToString(ArrayNode *values) {
    reverse(values);
    int index = 0;
    while (index < values->length - 1 && !values->values[index]) {
        ++index;
    }

    char *result = createString(values->length);
    for (int i = index; i < values->length; ++i) {
        sprintf(result, "%s%d", result, values->values[i]);
    }
    return result;
}

static ArrayNode *createArrays(int length) {
    ArrayNode *values = (ArrayNode *) malloc(sizeof(ArrayNode));
    values->values = (int *) malloc(sizeof(int) * length);
    memset(values->values, 0, sizeof(int) * length);
    values->length = length;
    return values;
}

static char *createString(int length) {
    char *values = (char *) malloc(sizeof(char) * (length + 1));
    memset(values, '\0', sizeof(char) * (length + 1));
    return values;
}

static void reverse(ArrayNode *values) {
    int start = 0;
    int end = values->length - 1;
    while (start < end) {
        values->values[start] ^= values->values[end];
        values->values[end] ^= values->values[start];
        values->values[start] ^= values->values[end];

        ++start;
        --end;
    }
}

static int max(int i, int j) {
    int aux = ~((i > j) ? 1 : 0) + 1;
    return (i & aux) | (j & ~aux);
}
