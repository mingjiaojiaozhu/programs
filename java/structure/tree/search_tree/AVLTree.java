package structure.tree.search_tree;

public class AVLTree {
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
            if (getHeight(parent.left) - getHeight(parent.right) >= 2) {
                if (key < parent.left.key) {
                    parent = leftLeftRotation(parent);
                } else {
                    parent = leftRightRotation(parent);
                }
            }
        } else {
            parent.right = addNode(parent.right, key, value);
            if (getHeight(parent.right) - getHeight(parent.left) >= 2) {
                if (key > parent.right.key) {
                    parent = rightRightRotation(parent);
                } else {
                    parent = rightLeftRotation(parent);
                }
            }
        }
        parent.height = Math.max(getHeight(parent.left), getHeight(parent.right)) + 1;
        return parent;
    }

    private TreeNode eraseNode(TreeNode parent, int key) {
        if (null == parent) {
            return parent;
        }

        if (key == parent.key) {
            if (null != parent.left && null != parent.right) {
                TreeNode current = parent.right;
                while (null != current.left) {
                    current = current.left;
                }
                parent.key = current.key;
                parent.value = current.value;
                parent.right = eraseNode(parent.right, key);
            } else {
                parent = (null != parent.left) ? parent.left : parent.right;
            }
        } else if (key < parent.key) {
            parent.left = eraseNode(parent.left, key);
            if (getHeight(parent.right) - getHeight(parent.left) >= 2) {
                if (getHeight(parent.right.right) > getHeight(parent.right.left)) {
                    parent = rightRightRotation(parent);
                } else {
                    parent = rightLeftRotation(parent);
                }
            }
        } else {
            parent.right = eraseNode(parent.right, key);
            if (getHeight(parent.left) - getHeight(parent.right) >= 2) {
                if (getHeight(parent.left.right) < getHeight(parent.left.left)) {
                    parent = leftLeftRotation(parent);
                } else {
                    parent = leftRightRotation(parent);
                }
            }
        }

        if (null != parent) {
            parent.height = Math.max(getHeight(parent.left), getHeight(parent.right)) + 1;
        }
        return parent;
    }

    private int getHeight(TreeNode current) {
        if (null == current) {
            return 0;
        }
        return current.height;
    }

    private TreeNode leftLeftRotation(TreeNode current) {
        TreeNode child = current.left;
        current.left = child.right;
        child.right = current;

        current.height = Math.max(getHeight(current.left), getHeight(current.right)) + 1;
        child.height = Math.max(getHeight(child.left), getHeight(child.right)) + 1;
        return child;
    }

    private TreeNode rightRightRotation(TreeNode current) {
        TreeNode child = current.right;
        current.right = child.left;
        child.left = current;

        current.height = Math.max(getHeight(current.left), getHeight(current.right)) + 1;
        child.height = Math.max(getHeight(child.left), getHeight(child.right)) + 1;
        return child;
    }

    private TreeNode leftRightRotation(TreeNode current) {
        current.left = rightRightRotation(current.left);
        return leftLeftRotation(current);
    }

    private TreeNode rightLeftRotation(TreeNode current) {
        current.right = leftLeftRotation(current.right);
        return rightRightRotation(current);
    }

    private class TreeNode {
        public int key = 0;
        public int value = 0;
        public int height = 1;
        public TreeNode left = null;
        public TreeNode right = null;

        public TreeNode(int key, int value) {
            this.key = key;
            this.value = value;
        }
    }
}
