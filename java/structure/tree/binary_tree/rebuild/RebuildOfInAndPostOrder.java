package structure.tree.binary_tree.rebuild;

import java.util.Arrays;

public class RebuildOfInAndPostOrder {
    public TreeNode rebuild(int[] inOrder, int[] postOrder) {
        int pivot = postOrder[postOrder.length - 1];
        TreeNode parent = new TreeNode(pivot);
        if (1 == postOrder.length) {
            return parent;
        }

        int index = 0;
        while (index < postOrder.length && pivot != inOrder[index]) {
            ++index;
        }

        if (index > 0) {
            parent.left = rebuild(Arrays.copyOfRange(inOrder, 0, index), Arrays.copyOfRange(postOrder, 0, index));
        }
        if (index < postOrder.length - 1) {
            parent.right = rebuild(Arrays.copyOfRange(inOrder, index + 1, inOrder.length), Arrays.copyOfRange(postOrder, index, postOrder.length - 1));
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
