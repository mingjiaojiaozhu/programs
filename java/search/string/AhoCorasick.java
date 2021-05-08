package search.string;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;

public class AhoCorasick {
    public int[] search(String text, String[] patterns) {
        TreeNode root = getRoot(patterns);

        int[] result = new int[patterns.length];
        Arrays.fill(result, -1);
        TreeNode current = root;
        for (int i = 0; i < text.length(); ++i) {
            TreeNode aux = null;
            while (null == aux) {
                aux = current.next[text.charAt(i) - 'a'];
                if (current == root) {
                    break;
                }

                if (null == aux) {
                    current = current.failure;
                }
            }
            if (null != aux) {
                current = aux;
            }

            for (int index : current.indexes) {
                result[index] = i - patterns[index].length() + 1;
            }
        }
        return result;
    }

    private TreeNode getRoot(String[] patterns) {
        TreeNode root = new TreeNode();
        for (int i = 0; i < patterns.length; ++i) {
            TreeNode current = root;
            for (char value : patterns[i].toCharArray()) {
                int index = value - 'a';
                if (null == current.next[index]) {
                    current.next[index] = new TreeNode();
                }
                current = current.next[index];
            }
            current.indexes.add(i);
        }

        Queue<TreeNode> queue = new LinkedList<>();
        for (int i = 0; i < 26; ++i) {
            if (null != root.next[i]) {
                root.next[i].failure = root;
                queue.offer(root.next[i]);
            }
        }
        while (!queue.isEmpty()) {
            TreeNode current = queue.poll();
            for (int i = 0; i < 26; ++i) {
                if (null == current.next[i]) {
                    continue;
                }

                TreeNode child = current.next[i];
                TreeNode failure = current.failure;
                while (null != failure && null == failure.next[i]) {
                    failure = failure.failure;
                }
                if (null == failure) {
                    child.failure = root;
                } else {
                    child.failure = failure.next[i];
                    for (int index : failure.next[i].indexes) {
                        child.indexes.add(index);
                    }
                }
                queue.offer(child);
            }
        }
        return root;
    }

    private class TreeNode {
        public TreeNode[] next = null;
        public TreeNode failure = null;
        List<Integer> indexes = new ArrayList<>();

        public TreeNode() {
            next = new TreeNode[26];
            Arrays.fill(next, null);
        }
    }
}
