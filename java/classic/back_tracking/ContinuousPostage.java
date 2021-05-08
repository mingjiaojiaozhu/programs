package classic.back_tracking;

import java.util.Arrays;

public class ContinuousPostage {
    public int[] solution(int num, int count) {
        int[] result = new int[num];
        Arrays.fill(result, 0);
        int[] aux = new int[num + 1];
        Arrays.fill(aux, 0);
        aux[1] = 1;
        int[] ends = new int[(num * count) << 6];
        Arrays.fill(ends, Integer.MAX_VALUE);
        ends[0] = 0;
        search(num, count, 1, 1, ends, 0, aux, result);
        return result;
    }

    private int search(int num, int count, int start, int index, int[] ends, int maxValue, int[] aux, int[] result) {
        for (int i = 0; i <= aux[start - 1] * (count - 1); ++i) {
            if (ends[i] < count) {
                for (int j = 1; j <= count - ends[i]; ++j) {
                    if (ends[i + aux[start] * j] > ends[i] + j) {
                        ends[i + aux[start] * j] = ends[i] + j;
                    }
                }
            }
        }
        while (ends[index] < Integer.MAX_VALUE) {
            ++index;
        }

        if (start == num) {
            if (maxValue < index - 1) {
                System.arraycopy(aux, 1, result, 0, result.length);
                maxValue = index - 1;
            }
            return maxValue;
        }

        int[] pivot = ends.clone();
        for (int i = aux[start] + 1; i <= index; ++i) {
            if (ends[index - i] < count) {
                aux[start + 1] = i;
                maxValue = search(num, count, start + 1, index + 1, ends, maxValue, aux, result);
                System.arraycopy(pivot, 0, ends, 0, ends.length);
            }
        }
        return maxValue;
    }
}
