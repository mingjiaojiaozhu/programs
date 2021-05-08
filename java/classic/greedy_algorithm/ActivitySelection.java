package classic.greedy_algorithm;

import java.util.Arrays;
import java.util.Comparator;

public class ActivitySelection {
    public int solution(int[][] values) {
        Arrays.sort(values, new Comparator<int[]>() {
            @Override
            public int compare(int[] node1, int[] node2) {
                return node1[1] - node2[1];
            }
        });

        int end = values[0][1];
        int result = 1;
        for (int i = 1; i < values.length; ++i) {
            if (end <= values[i][0]) {
                end = values[i][1];
                ++result;
            }
        }
        return result;
    }
}
