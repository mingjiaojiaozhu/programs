package structure.tree.search_tree;

public class SplayTree {
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
                splay(current);
                return;
            }

            parent = current;
            if (key < current.key) {
                current = current.left;
            } else {
                current = current.right;
            }
        }
        current = addNode(parent, key, value);
        splay(current);
    }

    public void erase(int key) {
        if (null == _root) {
            return;
        }

        if (key == _root.key && (null == _root.left || null == _root.right)) {
            _root = (null != _root.left) ? _root.left : _root.right;
            return;
        }

        TreeNode current = _root;
        while (null != current) {
            if (key == current.key) {
                break;
            }

            if (key < current.key) {
                current = current.left;
            } else {
                current = current.right;
            }
        }

        if (null == current) {
            return;
        }

        splay(current);
        if (null == current.left || null == current.right) {
            _root = (null != current.left) ? current.left : current.right;
            return;
        }

        TreeNode child = current.right;
        TreeNode parent = current;
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
                splay(current);
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
                splay(current);
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
        TreeNode child = new TreeNode(key, value);
        if (key < parent.key) {
            parent.left = child;
        } else {
            parent.right = child;
        }
        return child;
    }

    private void eraseNode(TreeNode parent, TreeNode current, TreeNode child) {
        if (current == parent.left) {
            parent.left = child;
        } else {
            parent.right = child;
        }
    }

    private void splay(TreeNode pivot) {
        TreeNode aux = new TreeNode(0, 0);
        TreeNode left = aux;
        TreeNode right = aux;

        TreeNode current = _root;
        while (pivot != current) {
            if (pivot.key < current.key) {
                if (pivot.key < current.left.key) {
                    current = leftRotation(current);
                }
                right.left = current;
                right = current;
                current = current.left;
            } else {
                if (pivot.key > current.right.key) {
                    current = rightRotation(current);
                }
                left.right = current;
                left = current;
                current = current.right;
            }
        }

        left.right = current.left;
        right.left = current.right;
        current.left = aux.right;
        current.right = aux.left;
        _root = current;
    }

    private TreeNode leftRotation(TreeNode current) {
        TreeNode child = current.left;
        current.left = child.right;
        child.right = current;
        return child;
    }

    private TreeNode rightRotation(TreeNode current) {
        TreeNode child = current.right;
        current.right = child.left;
        child.left = current;
        return child;
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
