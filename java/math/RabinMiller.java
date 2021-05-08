package math;

public class RabinMiller {
    private static final int[] _primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

    public boolean isPrime(long num) {
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
