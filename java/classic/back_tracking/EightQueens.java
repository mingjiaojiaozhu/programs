package classic.back_tracking;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class EightQueens {
    public String[][] solution(int num) {
        List<String[]> result = new ArrayList<>();
        int[] aux = new int[num];
        Arrays.fill(aux, -1);
        search(num, 0, 0, 0, 0, aux, result);
        return result.toArray(new String[0][]);
    }

    private void search(int num, int row, int col, int left, int right, int[] aux, List<String[]> result) {
        if (row == num) {
            String[] lines = new String[num];
            for (int i = 0; i < num; i++) {
                char[] line = new char[num];
                Arrays.fill(line, '0');
                line[aux[i]] = '1';
                lines[i] = String.valueOf(line);
            }
            result.add(lines);
            return;
        }

        int mask = ((1 << num) - 1) & (~(col | left | right));
        while (0 != mask) {
            int pos = mask & (~mask + 1);
            mask &= mask - 1;
            aux[row] = getBits(pos - 1);
            search(num, row + 1, col | pos, (left | pos) << 1, (right | pos) >> 1, aux, result);
            aux[row] = -1;
        }
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
