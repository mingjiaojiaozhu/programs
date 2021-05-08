#include <iostream>
#include <vector>
using namespace std;

class RabinMiller {
public:
    RabinMiller() {
        int aux[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
        primes.assign(aux, aux + 10);
    }

    bool isPrime(long long num) {
        if (primes.end() != find(primes.begin(), primes.end(), num)) {
            return true;
        }
        if (num < 2 || !(num & 1)) {
            return false;
        }

        long long base = num - 1;
        int index = 0;
        while (!(base & 1)) {
            base >>= 1;
            ++index;
        }

        for (int value : primes) {
            if (check(value, num, base, index)) {
                return false;
            }
        }
        return true;
    }

private:
    vector<int> primes;

    bool check(long long factor, long long num, long long base, int index) {
        long long pivot = powerMod(factor, base, num);
        if (1 == pivot) {
            return false;
        }

        while (index) {
            long long value = multiplyMod(pivot, pivot, num);
            if (1 == value && 1 != pivot && pivot != num - 1) {
                return true;
            }
            pivot = value;
            --index;
        }
        return 1 != pivot;
    }

    long long powerMod(long long base, long long index, long long mod) {
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

    long long multiplyMod(long long i, long long j, long long mod) {
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
};
