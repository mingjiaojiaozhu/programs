#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **values;
    int length;
} ArrayNode;

static void addValues(char **values, int index, int value);
static int greater(char *num1, int length1, char *num2, int length2);
static char *fillTail(char *num, int length);
static void reverse(char **result, int start, int end);
static int max(int i, int j);

void add(char *num1, char *num2, char **result) {
    int length1 = strlen(num1);
    int length2 = strlen(num2);
    int length = max(length1, length2);
    *result = (char *) malloc(sizeof(char) * (length + 2));
    memset(*result, '\0', sizeof(char) * (length + 2));
    int carry = 0;
    for (int i = 1; i <= length; ++i) {
        int value1 = (i <= length1) ? num1[length1 - i] - '0' : 0;
        int value2 = (i <= length2) ? num2[length2 - i] - '0' : 0;
        int value = value1 + value2 + carry;
        carry = value / 10;
        sprintf(*result, "%s%d", *result, value % 10);
    }
    if (carry) {
        sprintf(*result, "%s%d", *result, carry);
    }
    reverse(result, 0, strlen(*result) - 1);
}

void subtract(char *num1, char *num2, char **result) {
    int length1 = strlen(num1);
    int length2 = strlen(num2);
    if (!greater(num1, length1, num2, length2)) {
        subtract(num2, num1, result);
        int length = strlen(*result);
        memcpy(*result + 1, *result, sizeof(char) * length);
        (*result)[0] = '-';
        (*result)[length + 1] = '\0';
        return;
    }

    *result = (char *) malloc(sizeof(char) * (length1 + 2));
    memset(*result, '\0', sizeof(char) * (length1 + 2));
    int borrow = 0;
    for (int i = 1; i <= length1; ++i) {
        int value1 = num1[length1 - i] - '0';
        int value2 = (i <= length2) ? num2[length2 - i] - '0' : 0;
        int value = value1 - value2 - borrow;
        borrow = 0;
        if (value < 0) {
            value += 10;
            borrow = 1;
        }
        sprintf(*result, "%s%d", *result, value);
    }

    int index = strlen(*result) - 1;
    while (index > 0 && '0' == (*result)[index]) {
        --index;
    }
    (*result)[index + 1] = '\0';
    reverse(result, 0, index);
}

void multiply(char *num1, char *num2, char **result) {
    int length1 = strlen(num1);
    int length2 = strlen(num2);
    char *values = (char *) malloc(sizeof(char) * (length1 + length2));
    memset(values, '0', sizeof(char) * (length1 + length2));
    for (int i = 1; i <= length1; ++i) {
        int value1 = num1[length1 - i] - '0';
        for (int j = 1; j <= length2; ++j) {
            int value2 = num2[length2 - j] - '0';
            int value = value1 * value2;
            int index = i + j - 2;
            addValues(&values, index, value % 10);
            addValues(&values, index + 1, value / 10);
        }
    }

    int index = length1 + length2 - 1;
    while (index > 0 && '0' == values[index]) {
        --index;
    }
    *result = (char *) malloc(sizeof(char) * (length1 + length2 + 1));
    memset(*result, '\0', sizeof(char) * (length1 + length2 + 1));
    for (int i = index; i >= 0; --i) {
        sprintf(*result, "%s%c", *result, values[i]);
    }
}

void divide(char *num1, char *num2, ArrayNode *result) {
    int length1 = strlen(num1);
    int length2 = strlen(num2);
    result->values = (char **) malloc(sizeof(char *) * 2);
    result->values[0] = (char *) malloc(sizeof(char) * (length1 - length2 + 2));
    memset(result->values[0], '\0', sizeof(char) * (length1 - length2 + 2));
    result->values[1] = (char *) malloc(sizeof(char) * (length1 + 1));
    memset(result->values[1], '\0', sizeof(char) * (length1 + 1));
    for (int i = 0; i < 2; ++i) {
        result->values[i][0] = '0';
    }
    result->length = 2;

    char *aux = (char *) malloc(sizeof(char) * (length1 + 1));
    memcpy(aux, num1, sizeof(char) * length1);
    aux[length1] = '\0';
    num1 = aux;
    while (greater(num1, length1, num2, length2)) {
        int diff = length1 - length2;
        char *aux1 = fillTail(num2, diff);
        char *aux2 = fillTail("1", diff);
        int auxLength1 = strlen(aux1);
        if (!greater(num1, length1, aux1, auxLength1)) {
            aux1[auxLength1 - 1] = '\0';
            aux2[strlen(aux2) -1] = '\0';
            --auxLength1;
        }
        while (greater(num1, length1, aux1, auxLength1)) {
            char *result1 = "";
            subtract(num1, aux1, &result1);
            length1 = strlen(result1);
            memcpy(num1, result1, sizeof(char) * length1);
            num1[length1] = '\0';

            char *result2 = "";
            add(result->values[0], aux2, &result2);
            memcpy(result->values[0], result2, sizeof(char) * strlen(result2));
            result->values[0][strlen(result2)] = '\0';
        }
    }
    memcpy(result->values[1], num1, sizeof(char) * length1);
    result->values[1][length1] = '\0';
}

static void addValues(char **values, int index, int value) {
    (*values)[index] += value;
    if ((*values)[index] > '9') {
        (*values)[index] -= 10;
        ++(*values)[index + 1];
    }
}

static int greater(char *num1, int length1, char *num2, int length2) {
    if (length1 != length2) {
        return (length1 > length2) ? 1 : 0;
    }
    return (memcmp(num1, num2, length1) >= 0) ? 1 : 0;
}

static char *fillTail(char *num, int length) {
    char *result = (char *) malloc(sizeof(char) * (strlen(num) + length + 1));
    memcpy(result, num, sizeof(char) * strlen(num));
    memset(result + strlen(num), '0', sizeof(char) * length);
    result[strlen(num) + length] = '\0';
    return result;
}

static void reverse(char **result, int start, int end) {
    while (start < end) {
        char aux = (*result)[start];
        (*result)[start] = (*result)[end];
        (*result)[end] = aux;

        ++start;
        --end;
    }
}

static int max(int i, int j) {
    int aux = ~((i > j) ? 1 : 0) + 1;
    return (i & aux) | (j & ~aux);
}
