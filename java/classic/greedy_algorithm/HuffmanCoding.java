package classic.greedy_algorithm;

import java.util.Arrays;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.Stack;

public class HuffmanCoding {
    public String solution(String text) {
        List<Character> aux = Arrays.asList(text.chars().mapToObj(c -> (char) c).toArray(Character[]::new));
        int maxValue = Collections.max(aux);
        int minValue = Collections.min(aux);
        TreeNode[] arrays = new TreeNode[maxValue - minValue + 1];
        Arrays.fill(arrays, null);

        TreeNode current = getRoot(text, maxValue - minValue + 1, minValue, arrays);
        Stack<TreeNode> stack = new Stack<>();
        while (null != current || !stack.isEmpty()) {
            while (null != current) {
                String code = current.code.toString();
                stack.push(current);

                current = current.left;
                if (null != current) {
                    current.code.append(code).append("0");
                }
            }

            current = stack.pop();
            String code = current.code.toString();

            current = current.right;
            if (null != current) {
                current.code.append(code).append("1");
            }
        }

        StringBuffer result = new StringBuffer();
        for (char value : text.toCharArray()) {
            result.append(arrays[value - minValue].code);
        }
        return result.toString();
    }

    private TreeNode getRoot(String text, int size, int minValue, TreeNode[] arrays) {
        int[] bucktes = new int[size];
        Arrays.fill(bucktes, 0);
        for (char value : text.toCharArray()) {
            ++bucktes[value - minValue];
        }

        Queue<TreeNode> queue = new PriorityQueue<>(cmp);
        for (int i = 0; i < bucktes.length; ++i) {
            TreeNode node = new TreeNode(bucktes[i], null, null);
            queue.offer(node);
            arrays[i] = node;
        }

        while (queue.size() > 1) {
            TreeNode left = queue.poll();
            TreeNode right = queue.poll();
            queue.offer(new TreeNode(left.weight + right.weight, left, right));
        }
        return queue.poll();
    }

    private class TreeNode {
        public int weight = 0;
        public TreeNode left = null;
        public TreeNode right = null;
        public StringBuffer code = new StringBuffer();

        public TreeNode(int weight, TreeNode left, TreeNode right) {
            this.weight = weight;
            this.left = left;
            this.right = right;
        }
    }

    private static Comparator<TreeNode> cmp = new Comparator<TreeNode>() {
        @Override
        public int compare(TreeNode node1, TreeNode node2) {
            return node1.weight - node2.weight;
        }
    };
}
