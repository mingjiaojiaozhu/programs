package math;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Random;

public class PollardRho {
    private static final int[] _primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
    private static final Random _random = new Random();

    public long[] solution(long num) {
        List<Long> result = new ArrayList<>();
        if (num > 1) {
            factorization(num, 256, result);
        }
        Collections.sort(result);
        return result.stream().mapToLong(Long::valueOf).toArray();
    }

    private void factorization(long num, int aux, List<Long> result) {
        if (isPrime(num)) {
            result.add(num);
            return;
        }

        long factor = num;
        while (factor >= num) {
            factor = getFactor(factor, aux - 1);
            --aux;
        }
        factorization(factor, aux, result);
        factorization(num / factor, aux, result);
    }

    private boolean isPrime(long num) {
        if (exists(num)) {
            return true;
        }
        if (num < 2 || 0 == (num & 1)) {
            return false;
        }

        long base = num - 1;
        int index = 0;
        while (0 == (base & 1)) {
            base >>= 1;
            ++index;
        }

        for (int value : _primes) {
            if (check((long) value, num, base, index)) {
                return false;
            }
        }
        return true;
    }

    private long getFactor(long num, int aux) {
        long pivot = Math.abs(_random.nextLong()) % (num - 1) + 1;
        long value = (multiplyMod(pivot, pivot, num) + aux) % num;
        long index = 1;
        long base = 2;
        while (value != pivot) {
            long factor = gcd(pivot - value, num);
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

    private boolean check(long factor, long num, long base, int index) {
        long pivot = powerMod(factor, base, num);
        if (1 == pivot) {
            return false;
        }

        while (0 != index) {
            long value = multiplyMod(pivot, pivot, num);
            if (1 == value && 1 != pivot && pivot != num - 1) {
                return true;
            }
            pivot = value;
            --index;
        }
        return 1 != pivot;
    }

    private long powerMod(long base, long index, long mod) {
        base %= mod;
        if (1 == index) {
            return base;
        }

        long aux = base;
        long result = 1;
        while (0 != index) {
            if (0 != (index & 1)) {
                result = multiplyMod(result, aux, mod);
            }
            aux = multiplyMod(aux, aux, mod);
            index >>= 1;
        }
        return result;
    }

    private long multiplyMod(long i, long j, long mod) {
        i %= mod;
        j %= mod;
        long result = 0;
        while (0 != j) {
            if (0 != (j & 1)) {
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

    private long gcd(long num1, long num2) {
        return (0 ==num2) ? num1 : gcd(num2, num1 % num2);
    }

    private boolean exists(long num) {
        int start = 0;
        int end = _primes.length - 1;
        while (start <= end) {
            int middle = start + ((end - start) >> 1);
            if (num == _primes[middle]) {
                return true;
            }

            if (num < _primes[middle]) {
                end = middle - 1;
            } else {
                start = middle + 1;
            }
        }
        return false;
    }
}
