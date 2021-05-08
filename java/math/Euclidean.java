package math;

public class Euclidean {
    public int gcd(int num1, int num2) {
        return 0 == num2 ? num1 : gcd(num2, num1 % num2);
    }

    public int lcm(int num1, int num2) {
        return num1 / gcd(num1, num2) * num2;
    }
}
