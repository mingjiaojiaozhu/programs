package classic.greedy_algorithm;

import java.util.Arrays;
import java.util.Comparator;

public class IntervalCoverage {
    public int solution(int[][] values, int[] target) {
        Arrays.sort(values, new Comparator<int[]>() {
            @Override
            public int compare(int[] node1, int[] node2) {
                return node1[0] - node2[0];
            }
        });

        int start = target[0];
        int end = target[1];
        int index = 0;
        int result = 0;
        while (start < end) {
            int border = start;
            while (index < values.length && start >= values[index][0]) {
                if (border < values[index][1]) {
                    border = values[index][1];
                }
                ++index;
            }

            if (border == start) {
                return -1;
            }

            ++result;
            start = border;
        }
        return result;
    }
}
