package math;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class EulerTotientFunction {
    public int[] solution(int num) {
        boolean[] isPrime = new boolean[num];
        Arrays.fill(isPrime, true);
        List<Integer> primes = new ArrayList<>();

        int[] result = new int[num];
        Arrays.fill(result, 0);
        for (int i = 2; i <= num; ++i) {
            if (isPrime[i - 1]) {
                primes.add(i);
                result[i - 1] = i - 1;
            }

            for (int value : primes) {
                if (value > num / i) {
                    break;
                }

                isPrime[i * value - 1] = false;
                if (0 == i % value) {
                    result[i * value - 1] = result[i - 1] * value;
                    break;
                } else {
                    result[i * value - 1] = result[i - 1] * (value - 1);
                }
            }
        }
        return result;
    }
}
