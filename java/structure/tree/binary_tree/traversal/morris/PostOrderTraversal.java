package structure.tree.binary_tree.traversal.morris;

import java.util.ArrayList;
import java.util.List;

public class PostOrderTraversal {
    public int[] traversal(TreeNode root) {
        List<Integer> result = new ArrayList<>();
        TreeNode current = root;
        while (null != current) {
            if (null == current.left) {
                current = current.right;
                continue;
            }

            TreeNode aux = current.left;
            while (null != aux.right && aux.right != current) {
                aux = aux.right;
            }
            if (null == aux.right) {
                aux.right = current;
                current = current.left;
            } else {
                aux.right = null;
                traversal(current.left, result);
                current = current.right;
            }
        }
        traversal(root, result);
        return result.stream().mapToInt(Integer::valueOf).toArray();
    }

    private void traversal(TreeNode parent, List<Integer> result) {
        TreeNode tail = reverse(parent);
        TreeNode current = tail;
        while (null != current) {
            result.add(current.value);
            current = current.right;
        }
        reverse(tail);
    }

    TreeNode reverse(TreeNode current) {
        TreeNode prev = null;
        while (null != current) {
            TreeNode next = current.right;
            current.right = prev;
            prev = current;
            current = next;
        }
        return prev;
    }

    public class TreeNode {
        public int value = 0;
        public TreeNode left = null;
        public TreeNode right = null;

        public TreeNode(int value) {
            this.value = value;
        }
    }
}
