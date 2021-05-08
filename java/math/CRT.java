package math;

public class CRT {
    public int solution(int[][] values) {
        int total = 1;
        for (int[] value : values) {
            total *= value[0];
        }

        int result = 0;
        for (int[] value : values) {
            int lcm = total / value[0];
            result = (result + lcm / gcd(lcm, value[0])[0] * value[1]) % total;
        }
        return (result + total) % total;
    }

    private int[] gcd(int num1, int num2) {
        if (0 == num2) {
            return new int[]{1, 0};
        }

        int[] result = gcd(num2, num1 % num2);
        int aux = result[0] - result[1] * (num1 / num2);
        result[0] = result[1];
        result[1] = aux;
        return result;
    }
}
