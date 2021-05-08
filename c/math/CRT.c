#include <stdio.h>
#include <stdlib.h>

static int *gcd(int num1, int num2);

int crt(int **values, int length) {
    int total = 1;
    for (int i = 0; i < length; ++i) {
        total *= values[i][0];
    }

    int result = 0;
    for (int i = 0; i < length; ++i) {
        int lcm = total / values[i][0];
        result = (result + lcm / gcd(lcm, values[i][0])[0] * values[i][1]) % total;
    }
    return (result + total) % total;
}

static int *gcd(int num1, int num2) {
    if (!num2) {
        int *result = (int *) malloc(sizeof(int) * 2);
        result[0] = 1;
        result[1] = 0;
        return result;
    }

    int *result = gcd(num2, num1 % num2);
    int aux = result[0] - result[1] * (num1 / num2);
    result[0] = result[1];
    result[1] = aux;
    return result;
}
