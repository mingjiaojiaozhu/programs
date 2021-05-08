#include <stdio.h>
#include <stdlib.h>

static const int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

static int check(long long factor, long long num, long long base, int index);
static long long powerMod(long long base, long long index, long long mod);
static long long multiplyMod(long long i, long long j, long long mod);
static int exists(long long num);

int rabinMiller(long long num) {
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
