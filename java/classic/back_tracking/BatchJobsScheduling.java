package classic.back_tracking;

import java.util.Arrays;

public class BatchJobsScheduling {
    public int[] solution(int[][] values) {
        int[] result = new int[values.length];
        Arrays.fill(result, 0);
        int[] aux = new int[values.length];
        for (int i = 0; i < values.length; ++i) {
            aux[i] = i;
        }
        int[] ends = new int[3];
        Arrays.fill(ends, 0);
        search(values, 0, ends, Integer.MAX_VALUE, aux, result);
        return result;
    }

    private int search(int[][] values, int start, int[] ends, int minValue, int[] aux, int[] result) {
        if (start == values.length) {
            System.arraycopy(aux, 0, result, 0, result.length);
            return ends[2];
        }

        for (int i = start; i < values.length; ++i) {
            ends[0] += values[aux[i]][0];
            int pivot = ends[1];
            ends[1] = Math.max(ends[0], ends[1]) + values[aux[i]][1];
            ends[2] += ends[1];
            if (ends[2] < minValue) {
                swap(aux, start, i);
                minValue = search(values, start + 1, ends, minValue, aux, result);
                swap(aux, start, i);
            }
            ends[0] -= values[aux[i]][0];
            ends[2] -= ends[1];
            ends[1] = pivot;
        }
        return minValue;
    }

    private void swap(int[] nums, int i, int j) {
        if (i != j) {
            nums[i] ^= nums[j];
            nums[j] ^= nums[i];
            nums[i] ^= nums[j];
        }
    }
}
