package structure.tree.binary_tree.traversal;

import java.util.ArrayList;
import java.util.List;
import java.util.Stack;

public class PreOrderTraversal {
    public int[] traversal(TreeNode root) {
        List<Integer> result = new ArrayList<>();
        Stack<TreeNode> stack = new Stack<>();
        TreeNode current = root;
        while (null != current || !stack.isEmpty()) {
            while (null != current) {
                result.add(current.value);

                stack.push(current);
                current = current.left;
            }
            current = stack.pop().right;
        }
        return result.stream().mapToInt(Integer::valueOf).toArray();
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
