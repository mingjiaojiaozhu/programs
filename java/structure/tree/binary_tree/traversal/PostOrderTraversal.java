package structure.tree.binary_tree.traversal;

import java.util.ArrayList;
import java.util.List;
import java.util.Stack;

public class PostOrderTraversal {
    public int[] traversal(TreeNode root) {
        List<Integer> result = new ArrayList<>();
        Stack<TreeNode> stack = new Stack<>();
        stack.push(root);
        TreeNode current = null;
        while (!stack.isEmpty()) {
            TreeNode aux = stack.peek();
            if (null != aux.left && current != aux.left && current != aux.right) {
                stack.push(aux.left);
            } else if (null != aux.right && current != aux.right) {
                stack.push(aux.right);
            } else {
                result.add(aux.value);
                current = aux;
                stack.pop();
            }
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
