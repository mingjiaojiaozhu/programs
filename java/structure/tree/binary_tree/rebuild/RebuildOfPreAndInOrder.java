package structure.tree.binary_tree.rebuild;

import java.util.Arrays;

public class RebuildOfPreAndInOrder {
    public TreeNode rebuild(int[] preOrder, int[] inOrder) {
        int pivot = preOrder[0];
        TreeNode parent = new TreeNode(pivot);
        if (1 == preOrder.length) {
            return parent;
        }

        int index = 0;
        while (index <= preOrder.length && pivot != inOrder[index]) {
            ++index;
        }

        if (index > 0) {
            parent.left = rebuild(Arrays.copyOfRange(preOrder, 1, index + 1), Arrays.copyOfRange(inOrder, 0, index));
        }
        if (index < preOrder.length - 1) {
            parent.right = rebuild(Arrays.copyOfRange(preOrder, index + 1, preOrder.length), Arrays.copyOfRange(inOrder, index + 1, inOrder.length));
        }
        return parent;
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
