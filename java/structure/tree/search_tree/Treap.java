package structure.tree.search_tree;

import java.util.Random;

public class Treap {
    private TreeNode _root = null;

    public boolean isEmpty() {
        return null == _root;
    }

    public void add(int key, int value) {
        _root = addNode(_root, key, value);
    }

    public void erase(int key) {
        _root = eraseNode(_root, key);
    }

    public void set(int key, int value) {
        TreeNode current = _root;
        while (null != current) {
            if (key == current.key) {
                current.value = value;
                return;
            }

            if (key < current.key) {
                current = current.left;
            } else {
                current = current.right;
            }
        }
    }

    public int get(int key) {
        TreeNode current = _root;
        while (null != current) {
            if (key == current.key) {
                return current.value;
            }

            if (key < current.key) {
                current = current.left;
            } else {
                current = current.right;
            }
        }
        return Integer.MIN_VALUE;
    }

    public void clear() {
        _root = null;
    }

    private TreeNode addNode(TreeNode parent, int key, int value) {
        if (null == parent) {
            return new TreeNode(key, value);
        }

        if (key == parent.key) {
            parent.value = value;
            return parent;
        }

        if (key < parent.key) {
            parent.left = addNode(parent.left, key, value);
            if (parent.factor < parent.left.factor) {
                parent = rightRotation(parent);
            }
        } else {
            parent.right = addNode(parent.right, key, value);
            if (parent.factor < parent.right.factor) {
                parent = leftRotation(parent);
            }
        }
        return parent;
    }

    private TreeNode eraseNode(TreeNode parent, int key) {
        if (null == parent) {
            return parent;
        }

        if (key == parent.key) {
            if (null != parent.left && null != parent.right) {
                if (parent.left.factor > parent.right.factor) {
                    parent = rightRotation(parent);
                    parent.right = eraseNode(parent.right, key);
                } else {
                    parent = leftRotation(parent);
                    parent.left = eraseNode(parent.left, key);
                }
            } else {
                parent = (null != parent.left) ? parent.left : parent.right;
            }
        } else if (key < parent.key) {
            parent.left = eraseNode(parent.left, key);
        } else {
            parent.right = eraseNode(parent.right, key);
        }
        return parent;
    }

    private TreeNode leftRotation(TreeNode current) {
        TreeNode child = current.right;
        current.right = child.left;
        child.left = current;
        return child;
    }

    private TreeNode rightRotation(TreeNode current) {
        TreeNode child = current.left;
        current.left = child.right;
        child.right = current;
        return child;
    }

    private class TreeNode {
        public int key = 0;
        public int value = 0;
        public int factor = 1;
        public TreeNode left = null;
        public TreeNode right = null;

        public TreeNode(int key, int value) {
            this.key = key;
            this.value = value;
            this.factor = new Random().nextInt(65536);
        }
    }
}
