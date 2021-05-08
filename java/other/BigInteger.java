package other;

import java.util.Arrays;

public class BigInteger {
    public String add(String num1, String num2) {
        StringBuffer result = new StringBuffer();
        int carry = 0;
        for (int i = 1; i <= Math.max(num1.length(), num2.length()); ++i) {
            int value1 = (i <= num1.length()) ? num1.charAt(num1.length() - i) - '0' : 0;
            int value2 = (i <= num2.length()) ? num2.charAt(num2.length() - i) - '0' : 0;
            int value = value1 + value2 + carry;
            carry = value / 10;
            result.append(value % 10);
        }
        if (0 != carry) {
            result.append(carry);
        }
        return result.reverse().toString();
    }

    public String subtract(String num1, String num2) {
        if (!greater(num1, num2)) {
            return "-" + subtract(num2, num1);
        }

        StringBuffer result = new StringBuffer();
        int borrow = 0;
        for (int i = 1; i <= num1.length(); ++i) {
            int value1 = num1.charAt(num1.length() - i) - '0';
            int value2 = (i <= num2.length()) ? num2.charAt(num2.length() - i) - '0' : 0;
            int value = value1 - value2 - borrow;
            borrow = 0;
            if (value < 0) {
                value += 10;
                borrow = 1;
            }
            result.append(value);
        }

        int index = result.length() - 1;
        while (index > 0 && '0' == result.charAt(index)) {
            --index;
        }
        return result.reverse().toString().substring(result.length() - 1 - index);
    }

    public String multiply(String num1, String num2) {
        char[] values = new char[num1.length() + num2.length()];
        Arrays.fill(values, '0');
        for (int i = 1; i <= num1.length(); ++i) {
            int value1 = num1.charAt(num1.length() - i) - '0';
            for (int j = 1; j <= num2.length(); ++j) {
                int value2 = num2.charAt(num2.length() - j) - '0';
                int value = value1 * value2;
                int index = i + j - 2;
                addValues(values, index, value % 10);
                addValues(values, index + 1, value / 10);
            }
        }

        int index = values.length - 1;
        while (index > 0 && '0' == values[index]) {
            --index;
        }
        StringBuffer result = new StringBuffer();
        for (int i = index; i > 0; --i) {
            result.append(values[i]);
        }
        return result.toString();
    }

    public String[] divide(String num1, String num2) {
        String[] result = new String[2];
        Arrays.fill(result, "0");
        while (greater(num1, num2)) {
            int diff = num1.length() - num2.length();
            String aux1 = fillTail(num2, diff);
            String aux2 = fillTail("1", diff);
            if (!greater(num1, aux1)) {
                aux1 = aux1.substring(0, aux1.length() - 1);
                aux2 = aux2.substring(0, aux2.length() - 1);
            }
            while (greater(num1, aux1)) {
                num1 = subtract(num1, aux1);
                result[0] = add(result[0], aux2);
            }
        }
        result[1] = num1;
        return result;
    }

    private void addValues(char[] values, int index, int value) {
        values[index] += value;
        if (values[index] > '9') {
            values[index] -= 10;
            ++values[index + 1];
        }
    }

    private boolean greater(String num1, String num2) {
        if (num1.length() != num2.length()) {
            return num1.length() > num2.length();
        }
        return num1.compareTo(num2) >= 0;
    }

    private String fillTail(String num, int length) {
        return (0 != length) ? num + String.format("%0" + length + "d", 0) : num;
    }
}
