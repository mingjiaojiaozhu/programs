package structure.tree.search_tree;

public class BinarySearchTree {
    private TreeNode _root = null;

    public boolean isEmpty() {
        return null == _root;
    }

    public void add(int key, int value) {
        if (null == _root) {
            _root = new TreeNode(key, value);
            return;
        }

        TreeNode parent = null;
        TreeNode current = _root;
        while (null != current) {
            if (key == current.key) {
                current.value = value;
                return;
            }

            parent = current;
            if (key < current.key) {
                current = current.left;
            } else {
                current = current.right;
            }
        }
        addNode(parent, key, value);
    }

    public void erase(int key) {
        if (null == _root) {
            return;
        }

        if (key == _root.key && (null == _root.left || null == _root.right)) {
            _root = (null != _root.left) ? _root.left : _root.right;
            return;
        }

        TreeNode parent = null;
        TreeNode current = _root;
        while (null != current) {
            if (key == current.key) {
                break;
            }

            parent = current;
            if (key < current.key) {
                current = current.left;
            } else {
                current = current.right;
            }
        }

        if (null == current) {
            return;
        }

        if (null == current.left || null == current.right) {
            eraseNode(parent, current, (null != current.left) ? current.left : current.right);
            return;
        }

        TreeNode child = current.right;
        parent = current;
        while (null != child.left) {
            parent = child;
            child = child.left;
        }
        current.key = child.key;
        current.value = child.value;
        eraseNode(parent, child, child.right);
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

    private void addNode(TreeNode parent, int key, int value) {
        if (key < parent.key) {
            parent.left = new TreeNode(key, value);
        } else {
            parent.right = new TreeNode(key, value);
        }
    }

    private void eraseNode(TreeNode parent, TreeNode current, TreeNode child) {
        if (current == parent.left) {
            parent.left = child;
        } else {
            parent.right = child;
        }
    }

    private class TreeNode {
        public int key = 0;
        public int value = 0;
        public TreeNode left = null;
        public TreeNode right = null;

        public TreeNode(int key, int value) {
            this.key = key;
            this.value = value;
        }
    }
}
