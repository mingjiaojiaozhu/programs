#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    long long *values;
    int length;
    int capacity;
} ArrayNode;

static const int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

static void factorization(long long num, int aux, ArrayNode *result);
static int isPrime(long long num);
static long long getFactor(long long num, int aux);
static int check(long long factor, long long num, long long base, int index);
static long long powerMod(long long base, long long index, long long mod);
static long long multiplyMod(long long i, long long j, long long mod);
static long long gcd(long long num1, long long num2);
static int exists(long long num);
static int cmp(const void *p, const void *q);

void pollardRho(long long num, ArrayNode *result) {
    srand((unsigned int) time(NULL));
    result->values = (long long *) malloc(sizeof(long long) * 64);
    memset(result->values, 0, sizeof(long long) * 64);
    result->length = 0;
    result->capacity = 64;
    if (num > 1) {
        factorization(num, 256, result);
    }
    qsort(result->values, result->length, sizeof(long long), cmp);
}

static void factorization(long long num, int aux, ArrayNode *result) {
    if (isPrime(num)) {
        if (result->length >= result->capacity) {
            result->values = (long long *) realloc(result->values, sizeof(long long) * (result->capacity + 16));
            memset(result->values + result->capacity, 0, sizeof(long long) * 16);
            result->capacity += 16;
        }
        result->values[result->length] = num;
        ++result->length;
        return;
    }

    long long factor = num;
    while (factor >= num) {
        factor = getFactor(factor, aux - 1);
        --aux;
    }
    factorization(factor, aux, result);
    factorization(num / factor, aux, result);
}

static int isPrime(long long num) {
    if (exists(num)) {
        return 1;
    }
    if (num < 2 || !(num & 1)) {
        return 0;
    }

    long long base = num - 1;
    int index = 0;
    while (!(base & 1)) {
        base >>= 1;
        ++index;
    }

    for (int i = 0; i < 10; ++i) {
        if (check(primes[i], num, base, index)) {
            return 0;
        }
    }
    return 1;
}

static long long getFactor(long long num, int aux) {
    long long pivot = rand() % (num - 1) + 1;
    long long value = (multiplyMod(pivot, pivot, num) + aux) % num;
    long long index = 1;
    long long base = 2;
    while (value != pivot) {
        long long factor = gcd(pivot - value, num);
        if (factor > 1 && factor < num) {
            return factor;
        }

        ++index;
        if (index == base) {
            pivot = value;
            base <<= 1;
        }
        value = (multiplyMod(value, value, num) + aux) % num;
    }
    return num;
}

static int check(long long factor, long long num, long long base, int index) {
    long long pivot = powerMod(factor, base, num);
    if (1 == pivot) {
        return 0;
    }

    while (index) {
        long long value = multiplyMod(pivot, pivot, num);
        if (1 == value && 1 != pivot && pivot != num - 1) {
            return 1;
        }
        pivot = value;
        --index;
    }
    return (1 != pivot) ? 1 : 0;
}

static long long powerMod(long long base, long long index, long long mod) {
    base %= mod;
    if (1 == index) {
        return base;
    }

    long long aux = base;
    long long result = 1;
    while (index) {
        if (index & 1) {
            result = multiplyMod(result, aux, mod);
        }
        aux = multiplyMod(aux, aux, mod);
        index >>= 1;
    }
    return result;
}

static long long multiplyMod(long long i, long long j, long long mod) {
    i %= mod;
    j %= mod;
    long long result = 0;
    while (j) {
        if (j & 1) {
            result = (result + i) % mod;
        }
        i <<= 1;
        if (i >= mod) {
            i %= mod;
        }
        j >>= 1;
    }
    return result;
}

static long long gcd(long long num1, long long num2) {
    return !num2 ? num1 : gcd(num2, num1 % num2);
}

static int exists(long long num) {
    int start = 0;
    int end = 9;
    while (start <= end) {
        int middle = start + ((end - start) >> 1);
        if (num == primes[middle]) {
            return 1;
        }

        if (num < primes[middle]) {
            end = middle - 1;
        } else {
            start = middle + 1;
        }
    }
    return 0;
}

static int cmp(const void *p, const void *q) {
    return *((int *) p) - *((int *) q);
}
