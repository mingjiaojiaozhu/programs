package classic.divide_and_conquer;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.stream.Collectors;

public class Karatsuba {
    public String multiply(String num1, String num2) {
        int length = Math.max(num1.length(), num2.length());
        if (length <= 4) {
            return String.valueOf(Integer.parseInt(num1) * Integer.parseInt(num2));
        }

        if (length > num1.length()) {
            num1 = fillHead(num1, length - num1.length());
        }
        if (length > num2.length()) {
            num2 = fillHead(num2, length - num2.length());
        }

        int halfSize = length >> 1;
        String num1Head = num1.substring(0, halfSize);
        String num1Tail = num1.substring(halfSize);
        String num2Head = num2.substring(0, halfSize);
        String num2Tail = num2.substring(halfSize);
        String aux1 = multiply(num1Head, num2Head);
        String aux2 = multiply(num1Tail, num2Tail);
        return add(add(fillTail(aux1, (length - halfSize) << 1), fillTail(subtract(multiply(add(num1Head, num1Tail), add(num2Head, num2Tail)), add(aux1, aux2)), length - halfSize)), aux2);
    }

    private String add(String num1, String num2) {
        int[] values1 = stringToArrays(num1);
        int[] values2 = stringToArrays(num2);

        int[] result = new int[Math.max(num1.length(), num2.length()) + 1];
        Arrays.fill(result, 0);
        System.arraycopy(values1, 0, result, 0, values1.length);
        for (int i = 0; i < values2.length; ++i) {
            result[i] += values2[i];
            if (result[i] >= 10) {
                result[i] -= 10;
                ++result[i + 1];
            }
        }

        int index = values2.length;
        while (index < values1.length - 1 && result[index] >= 10) {
            result[index] -= 10;
            ++result[index + 1];
            ++index;
        }
        return arraysToString(result);
    }

    private String subtract(String num1, String num2) {
        int[] values1 = stringToArrays(num1);
        int[] values2 = stringToArrays(num2);
        for (int i = 0; i < values2.length; ++i) {
            values1[i] -= values2[i];
            if (values1[i] < 0) {
                values1[i] += 10;
                --values1[i + 1];
            }
        }

        int index = values2.length;
        while (index < values1.length - 1 && values1[index] < 0) {
            values1[index] += 10;
            --values1[index + 1];
            ++index;
        }
        return arraysToString(values1);
    }

    private String fillHead(String num, int length) {
        return String.format("%0" + length + "d", 0) + num;
    }

    private String fillTail(String num, int length) {
        return num + String.format("%0" + length + "d", 0);
    }

    private int[] stringToArrays(String num) {
        List<Integer> result = new ArrayList<>();
        for (char value : num.toCharArray()) {
            result.add(value - '0');
        }
        Collections.reverse(result);
        return result.stream().mapToInt(Integer::valueOf).toArray();
    }

    private String arraysToString(int[] values) {
        List<Integer> aux = Arrays.stream(values).boxed().collect(Collectors.toList());
        Collections.reverse(aux);
        int index = 0;
        while (index < aux.size() - 1 && 0 == aux.get(index)) {
            ++index;
        }

        StringBuffer result = new StringBuffer();
        for (int i = index; i < aux.size(); ++i) {
            result.append(aux.get(i));
        }
        return result.toString();
    }
}
