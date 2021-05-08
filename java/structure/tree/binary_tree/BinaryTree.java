package structure.tree.binary_tree;

import java.util.LinkedList;
import java.util.Queue;

public class BinaryTree {
    public boolean isPerfect(TreeNode root) {
        if (null == root) {
            return true;
        }

        Queue<TreeNode> queue = new LinkedList<>();
        queue.offer(root);

        int count = 0;
        boolean flag = false;
        while (!queue.isEmpty()) {
            TreeNode current = queue.poll();
            if (null == current) {
                flag = true;
                continue;
            }

            if (flag) {
                return false;
            }

            ++count;
            queue.offer(current.left);
            queue.offer(current.right);
        }
        return 0 == (count & (count + 1));
    }

    public boolean isCompleted(TreeNode root) {
        if (null == root) {
            return true;
        }

        Queue<TreeNode> queue = new LinkedList<>();
        queue.offer(root);

        boolean flag = false;
        while (!queue.isEmpty()) {
            TreeNode current = queue.poll();
            if ((null == current.left && null != current.right) || (flag && (null != current.left || null != current.right))) {
                return false;
            }

            if (null != current.left) {
                queue.offer(current.left);
            }
            if (null != current.right) {
                queue.offer(current.right);
            } else {
                flag = true;
            }
        }
        return true;
    }

    public boolean isFull(TreeNode root) {
        if (null == root) {
            return true;
        }

        Queue<TreeNode> queue = new LinkedList<>();
        queue.offer(root);
        while (!queue.isEmpty()) {
            TreeNode current = queue.poll();
            if ((null != current.left && null == current.right) || (null == current.left && null != current.right)) {
                return false;
            }

            if (null != current.left) {
                queue.offer(current.left);
            }
            if (null != current.right) {
                queue.offer(current.right);
            }
        }
        return true;
    }

    public int nodeNum(TreeNode root) {
        if (null == root) {
            return 0;
        }

        Queue<TreeNode> queue = new LinkedList<>();
        queue.offer(root);

        int count = 0;
        while (!queue.isEmpty()) {
            ++count;

            TreeNode current = queue.poll();
            if (null != current.left) {
                queue.offer(current.left);
            }
            if (null != current.right) {
                queue.offer(current.right);
            }
        }
        return count;
    }

    public int leafNodeNum(TreeNode root) {
        if (null == root) {
            return 0;
        }

        Queue<TreeNode> queue = new LinkedList<>();
        queue.offer(root);

        int count = 0;
        while (!queue.isEmpty()) {
            TreeNode current = queue.poll();
            if (null == current.left && null == current.right) {
                ++count;
                continue;
            }

            if (null != current.left) {
                queue.offer(current.left);
            }
            if (null != current.right) {
                queue.offer(current.right);
            }
        }
        return count;
    }

    public int maxDepth(TreeNode root) {
        if (null == root) {
            return 0;
        }

        Queue<TreeNode> queue = new LinkedList<>();
        queue.offer(root);

        int count = 0;
        while (!queue.isEmpty()) {
            ++count;

            int length = queue.size();
            for (int i = 0; i < length; ++i) {
                TreeNode current = queue.poll();
                if (null != current.left) {
                    queue.offer(current.left);
                }
                if (null != current.right) {
                    queue.offer(current.right);
                }
            }
        }
        return count;
    }

    public TreeNode mirror(TreeNode root) {
        if (null == root || (null == root.left && null == root.right)) {
            return root;
        }

        TreeNode aux = root.left;
        root.left = root.right;
        root.right = aux;

        root.left = mirror(root.left);
        root.right = mirror(root.right);
        return root;
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
