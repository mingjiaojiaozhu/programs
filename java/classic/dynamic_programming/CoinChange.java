package classic.dynamic_programming;

import java.util.Arrays;

public class CoinChange {
    public int solution(int[] values, int target) {
        int[] result = new int[target + 1];
        Arrays.fill(result, Integer.MAX_VALUE);
        result[0] = 0;
        for (int i = 0; i <= target; ++i) {
            for (int value : values) {
                if (i >= value) {
                    int pivot = result[i - value] + 1;
                    if (result[i] > pivot) {
                        result[i] = pivot;
                    }
                }
            }
        }
        return (result[result.length - 1] <= target) ? result[result.length - 1] : -1;
    }
}
