package classic.dynamic_programming;

import java.util.Arrays;

public class LongestIncreasingSubsequence {
    public int solution(int[] values) {
        int[] result = new int[values.length];
        Arrays.fill(result, 0);
        result[0] = 1;
        for (int i = 1; i < values.length; ++i) {
            result[i] = 1;
            for (int j = 0; j < i; ++j) {
                if (values[i] > values[j] && result[i] < result[j] + 1) {
                    result[i] = result[j] + 1;
                }
            }
        }
        return Arrays.stream(result).max().getAsInt();
    }
}
