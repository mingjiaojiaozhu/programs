#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;

class PollardRho {
public:
    PollardRho() {
        int aux[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
        primes.assign(aux, aux + 10);
    }

    vector<long long> solution(long long num) {
        srand((unsigned int) time(nullptr));
        vector<long long> result(0);
        if (num > 1) {
            factorization(num, 256, result);
        }
        sort(result.begin(), result.end());
        return result;
    }

private:
    vector<int> primes;

    void factorization(long long num, int aux, vector<long long> &result) {
        if (isPrime(num)) {
            result.emplace_back(num);
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

    long long getFactor(long long num, int aux) {
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

    long long gcd(long long num1, long long num2) {
        return !num2 ? num1 : gcd(num2, num1 % num2);
    }
};
