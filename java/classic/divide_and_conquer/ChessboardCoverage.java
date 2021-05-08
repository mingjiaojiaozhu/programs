package classic.divide_and_conquer;

import java.util.Arrays;

public class ChessboardCoverage {
    public int[][] solution(int k, int[] square) {
        int size = (int) Math.pow(2, k);
        int[][] result = new int[size][size];
        for (int i = 0; i < size; ++i) {
            Arrays.fill(result[i], 0);
        }
        cover(size, square[0], square[1], 0, 0, 1, result);
        return result;
    }

    private int cover(int size, int row, int col, int startRow, int startCol, int index, int[][] result) {
        size >>= 1;
        if (0 == size) {
            return index - 1;
        }

        int value = index;
        ++index;
        if (row < startRow + size && col < startCol + size) {
            index = cover(size, row, col, startRow, startCol, index, result);
        } else {
            result[startRow + size - 1][startCol + size - 1] = value;
            index = cover(size, startRow + size - 1, startCol + size - 1, startRow, startCol, index, result);
        }

        ++index;
        if (row < startRow + size && col >= startCol + size) {
            index = cover(size, row, col, startRow, startCol + size, index, result);
        } else {
            result[startRow + size - 1][startCol + size] = value;
            index = cover(size, startRow + size - 1, startCol + size, startRow, startCol + size, index, result);
        }

        ++index;
        if (row >= startRow + size && col < startCol + size) {
            index = cover(size, row, col, startRow + size, startCol, index, result);
        } else {
            result[startRow + size][startCol + size - 1] = value;
            index = cover(size, startRow + size, startCol + size - 1, startRow + size, startCol, index, result);
        }

        ++index;
        if (row >= startRow + size && col >= startCol + size) {
            index = cover(size, row, col, startRow + size, startCol + size, index, result);
        } else {
            result[startRow + size][startCol + size] = value;
            index = cover(size, startRow + size, startCol + size, startRow + size, startCol + size, index, result);
        }
        return index;
    }
}
