package structure.tree.binary_tree.traversal;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;

public class LevelOrderTraversal {
    public int[] traversal(TreeNode root) {
        List<Integer> result = new ArrayList<>();
        Queue<TreeNode> queue = new LinkedList<>();
        queue.offer(root);
        while (!queue.isEmpty()) {
            TreeNode current = queue.poll();
            result.add(current.value);

            if (null != current.left) {
                queue.offer(current.left);
            }
            if (null != current.right) {
                queue.offer(current.right);
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
