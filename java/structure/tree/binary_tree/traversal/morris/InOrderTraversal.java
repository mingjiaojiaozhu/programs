package structure.tree.binary_tree.traversal.morris;

import java.util.ArrayList;
import java.util.List;

public class InOrderTraversal {
    public int[] traversal(TreeNode root) {
        List<Integer> result = new ArrayList<>();
        TreeNode current = root;
        while (null != current) {
            if (null == current.left) {
                result.add(current.value);
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
                result.add(current.value);
                aux.right = null;
                current = current.right;
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
