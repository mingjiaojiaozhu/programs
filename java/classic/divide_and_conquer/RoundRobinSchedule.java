package classic.divide_and_conquer;

import java.util.Arrays;

public class RoundRobinSchedule {
    public int[][] solution(int k) {
        int size = (int) Math.pow(2, k);
        int[][] result = new int[size][size];
        for (int i = 0; i < size; ++i) {
            Arrays.fill(result[i], i);
        }
        schedule(size, 0, 0, result);
        return result;
    }

    private void schedule(int size, int startRow, int startCol, int[][] result) {
        size >>= 1;
        if (size > 1) {
            schedule(size, startRow, startCol, result);
            schedule(size, startRow + size, startCol, result);
        }

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                result[startRow + size + i][startCol + size + j] = result[startRow + i][startCol + j];
                result[startRow + i][startCol + size + j] = result[startRow + size + i][startCol + j];
            }
        }
    }
}
