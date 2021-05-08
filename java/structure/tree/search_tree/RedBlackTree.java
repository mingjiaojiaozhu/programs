package structure.tree.search_tree;

public class RedBlackTree {
    private static final char _red = '0';
    private static final char _black = '1';

    private TreeNode _root = null;

    public boolean isEmpty() {
        return null == _root;
    }

    public void add(int key, int value) {
        if (null == _root) {
            _root = new TreeNode(key, value, _black, null);
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
        TreeNode child = new TreeNode(key, value, _red, parent);
        if (key < parent.key) {
            parent.left = child;
        } else {
            parent.right = child;
        }
        addFixup(child);
    }

    private void eraseNode(TreeNode parent, TreeNode current, TreeNode child) {
        char color = current.color;
        if (current == parent.left) {
            parent.left = child;
        } else {
            parent.right = child;
        }

        if (null != child) {
            child.parent = parent;
        }

        if (_black == color) {
            eraseFixup(child, parent);
        }
    }

    private void addFixup(TreeNode current) {
        TreeNode parent = current.parent;
        while (null != parent && _red == parent.color) {
            TreeNode grandParent = parent.parent;
            if (parent == grandParent.left) {
                current = addFixupNode(current, parent, grandParent, grandParent.right, parent.right, true);
            } else {
                current = addFixupNode(current, parent, grandParent, grandParent.left, parent.left, false);
            }
            parent = current.parent;
        }
        _root.color = _black;
    }

    private void eraseFixup(TreeNode current, TreeNode parent) {
        while ((null == current || _black == current.color) && current != _root) {
            if (parent.left == current) {
                current = eraseFixupNode(parent, parent.right, true);
            } else {
                current = eraseFixupNode(parent, parent.left, false);
            }
            parent = current.parent;
        }

        if (null != current) {
            current.color = _black;
        }
    }

    private TreeNode addFixupNode(TreeNode current, TreeNode parent, TreeNode grandParent, TreeNode uncle, TreeNode brother, boolean isLeft) {
        if (null != uncle && _red == uncle.color) {
            uncle.color = _black;
            parent.color = _black;
            grandParent.color = _red;
            return grandParent;
        }

        if (brother == current) {
            if (isLeft) {
                leftRotation(parent);
            } else {
                rightRotation(parent);
            }

            TreeNode aux = parent;
            parent = current;
            current = aux;
        }

        parent.color = _black;
        grandParent.color = _red;
        if (isLeft) {
            rightRotation(grandParent);
        } else {
            leftRotation(grandParent);
        }
        return current;
    }

    private TreeNode eraseFixupNode(TreeNode parent, TreeNode brother, boolean isLeft) {
        if (_red == brother.color) {
            brother.color = _black;
            parent.color = _red;

            if (isLeft) {
                leftRotation(parent);
                brother = parent.right;
            } else {
                rightRotation(parent);
                brother = parent.left;
            }
        }

        if ((null == brother.left || _black == brother.left.color) && (null == brother.right || _black == brother.right.color)) {
            brother.color = _red;
            return parent;
        }

        if (isLeft && (null == brother.right || _black == brother.right.color)) {
            brother.left.color = _black;
            brother.color = _red;
            rightRotation(brother);
            brother = parent.right;
        }
        if (!isLeft && (null == brother.left || _black == brother.left.color)) {
            brother.right.color = _black;
            brother.color = _red;
            leftRotation(brother);
            brother = parent.left;
        }

        brother.color = parent.color;
        parent.color = _black;
        if (isLeft) {
            brother.right.color = _black;
            leftRotation(parent);
        } else {
            brother.left.color = _black;
            rightRotation(parent);
        }
        return _root;
    }

    private void leftRotation(TreeNode current) {
        TreeNode child = current.right;
        current.right = child.left;
        if (null != child.left) {
            child.left.parent = current;
        }
        child.parent = current.parent;

        if (null == current.parent) {
            _root = child;
        } else {
            if (current.parent.left == current) {
                current.parent.left = child;
            } else {
                current.parent.right = child;
            }
        }

        child.left = current;
        current.parent = child;
    }

    private void rightRotation(TreeNode current) {
        TreeNode child = current.left;
        current.left = child.right;
        if (null != child.right) {
            child.right.parent = current;
        }
        child.parent = current.parent;

        if (null == current.parent) {
            _root = child;
        } else {
            if (current.parent.left == current) {
                current.parent.left = child;
            } else {
                current.parent.right = child;
            }
        }

        child.right = current;
        current.parent = child;
    }

    private class TreeNode {
        public int key = 0;
        public int value = 0;
        public char color = '0';
        public TreeNode left = null;
        public TreeNode right = null;
        public TreeNode parent = null;

        public TreeNode(int key, int value, char color, TreeNode parent) {
            this.key = key;
            this.value = value;
            this.color = color;
            this.parent = parent;
        }
    }
}
