package math;

public class ExtendedEuclidean {
    public int[] gcd(int num1, int num2) {
        if (0 == num2) {
            return new int[]{num1, 1, 0};
        }

        int[] result = gcd(num2, num1 % num2);
        int aux = result[1] - result[2] * (num1 / num2);
        result[1] = result[2];
        result[2] = aux;
        return result;
    }
}
