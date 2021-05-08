package math;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class EulerSieve {
    public int[] sieve(int num) {
        boolean[] isPrime = new boolean[num];
        Arrays.fill(isPrime, true);
        List<Integer> result = new ArrayList<>();
        for (int i = 2; i <= num; ++i) {
            if (isPrime[i - 1]) {
                result.add(i);
            }

            for (int value : result) {
                if (value > num / i) {
                    break;
                }

                isPrime[i * value - 1] = false;
                if (0 == i % value) {
                    break;
                }
            }
        }
        return result.stream().mapToInt(Integer::valueOf).toArray();
    }
}
