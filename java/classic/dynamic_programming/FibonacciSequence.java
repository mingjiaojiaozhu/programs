package classic.dynamic_programming;

public class FibonacciSequence {
    public int[] solution(int num) {
        int result[] = new int[num];
        result[0] = 1;
        result[1] = 1;
        for (int i = 2; i < num; ++i) {
            result[i] = result[i - 1] + result[i - 2];
        }
        return result;
    }
}
