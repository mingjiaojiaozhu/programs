package classic.divide_and_conquer;

import java.util.List;

public class Hanoi {
    public void solution(List<Integer> values1, List<Integer> values2, List<Integer> values3) {
        move(values1.size(), values1, values2, values3);
    }

    private void move(int size, List<Integer> values1, List<Integer> values2, List<Integer> values3) {
        --size;
        if (0 == size) {
            values3.add(values1.get(values1.size() - 1));
            values1.remove(values1.size() - 1);
            return;
        }

        move(size, values1, values3, values2);
        values3.add(values1.get(values1.size() - 1));
        values1.remove(values1.size() - 1);
        move(size, values2, values1, values3);
    }
}
