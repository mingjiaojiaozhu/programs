package classic.dynamic_programming;

import java.util.Arrays;

public class KnapsackOfMultiple {
    public int solution(int[] weights, int[] values, int[] nums, int target) {
        int[] result = new int[target + 1];
        Arrays.fill(result, 0);
        for (int i = 0; i < weights.length; ++i) {
            int weight = weights[i];
            int value = values[i];
            int num = nums[i];
            for (int j = target; j >= weight; --j) {
                for (int k = 0; k <= Math.min(num, j / weight); ++k) {
                    int pivot = result[j - k * weight] + k * value;
                    if (result[j] < pivot) {
                        result[j] = pivot;
                    }
                }
            }
        }
        return result[result.length - 1];
    }
}
