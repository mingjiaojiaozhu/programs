package other;

import java.util.ArrayList;
import java.util.List;
import java.util.Stack;

public class RPN {
    public String[] converse(String[] values) {
        Stack<String> stack = new Stack<>();
        List<String> result = new ArrayList<>();
        for (String value : values) {
            if ("(".equals(value)) {
                stack.push(value);
                continue;
            }

            if (")".equals(value)) {
                while (!stack.isEmpty()) {
                    String sign = stack.pop();
                    if ("(".equals(sign)) {
                        break;
                    }
                    result.add(sign);
                }
                continue;
            }

            if (!"+".equals(value) && !"-".equals(value) && !"*".equals(value) && !"/".equals(value)) {
                result.add(value);
                continue;
            }

            while (!stack.isEmpty()) {
                String sign = stack.peek();
                if ("(".equals(sign) || (("*".equals(value) || "/".equals(value)) && ("+".equals(sign) || "-".equals(sign)))) {
                    break;
                }
                result.add(sign);
                stack.pop();
            }
            stack.push(value);
        }

        while (!stack.isEmpty()) {
            result.add(stack.pop());
        }
        return result.toArray(new String[result.size()]);
    }

    public int evaluate(String[] values) {
        Stack<Integer> stack = new Stack<>();
        for (String value : values) {
            if (!"+".equals(value) && !"-".equals(value) && !"*".equals(value) && !"/".equals(value)) {
                stack.push(Integer.parseInt(value));
                continue;
            }

            int num1 = stack.pop();
            int num2 = stack.pop();
            if ("+".equals(value)) {
                stack.push(num2 + num1);
            } else if ("-".equals(value)) {
                stack.push(num2 - num1);
            } else if ("*".equals(value)) {
                stack.push(num2 * num1);
            } else {
                stack.push(num2 / num1);
            }
        }
        return stack.peek();
    }
}
