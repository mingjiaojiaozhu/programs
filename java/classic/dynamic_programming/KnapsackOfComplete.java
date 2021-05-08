package classic.dynamic_programming;

import java.util.Arrays;

public class KnapsackOfComplete {
    public int solution(int[] weights, int[] values, int target) {
        int[] result = new int[target + 1];
        Arrays.fill(result, 0);
        for (int i = 0; i < weights.length; ++i) {
            int weight = weights[i];
            int value = values[i];
            for (int j = weight; j <= target; ++j) {
                int pivot = result[j - weight] + value;
                if (result[j] < pivot) {
                    result[j] = pivot;
                }
            }
        }
        return result[result.length - 1];
    }
}
