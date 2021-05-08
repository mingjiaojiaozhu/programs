package classic.back_tracking;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Sudoku {
    public void solution(int[][] nums) {
        int[] lines = new int[nums.length];
        Arrays.fill(lines, 0);
        int[] columns = new int[nums.length];
        Arrays.fill(columns, 0);
        int[][] blocks = new int[nums.length / 3][nums.length / 3];
        for (int i = 0; i < nums.length / 3; ++i) {
            Arrays.fill(blocks[i], 0);
        }
        for (int i = 0; i < nums.length; ++i) {
            for (int j = 0; j < nums.length; ++j) {
                if (0 != nums[i][j]) {
                    fill(lines, columns, blocks, i, j, nums[i][j] - 1);
                }
            }
        }

        while (true) {
            boolean flag = false;
            for (int i = 0; i < nums.length; ++i) {
                for (int j = 0; j < nums.length; ++j) {
                    if (0 == nums[i][j]) {
                        int mask = ~(lines[i] | columns[j] | blocks[i / 3][j / 3]) & 0x1ff;
                        if (0 == (mask & (mask - 1))) {
                            int digit = getBits(mask - 1);
                            fill(lines, columns, blocks, i, j, digit);
                            nums[i][j] = digit + 1;
                            flag = true;
                        }
                    }
                }
            }
            if (!flag) {
                break;
            }
        }

        List<int[]> spaces = new ArrayList<>();
        for (int i = 0; i < nums.length; ++i) {
            for (int j = 0; j < nums.length; ++j) {
                if (0 == nums[i][j]) {
                    spaces.add(new int[]{i, j});
                }
            }
        }
        search(nums, lines, columns, blocks, spaces, 0, false);
    }

    private boolean search(int[][] nums, int[] lines, int[] columns, int[][] blocks, List<int[]> spaces, int index, boolean flag) {
        if (index == spaces.size()) {
            return true;
        }

        int row = spaces.get(index)[0];
        int col = spaces.get(index)[1];
        int mask = ~(lines[row] | columns[col] | blocks[row / 3][col / 3]) & 0x1ff;
        while (0 != mask && !flag) {
            int pos = mask & (~mask + 1);
            mask &= (mask - 1);
            int digit = getBits(pos - 1);
            fill(lines, columns, blocks, row, col, digit);
            nums[row][col] = digit + 1;
            flag = search(nums, lines, columns, blocks, spaces, index + 1, flag);
            fill(lines, columns, blocks, row, col, digit);
        }
        return flag;
    }

    private void fill(int[] lines, int[] columns, int[][] blocks, int row, int col, int digit) {
        lines[row] ^= (1 << digit);
        columns[col] ^= (1 << digit);
        blocks[row / 3][col / 3] ^= (1 << digit);
    }

    private int getBits(int value) {
        int result = 0;
        while (0 != value) {
            ++result;
            value &= value - 1;
        }
        return result;
    }
}
