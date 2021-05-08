package structure.tree.heap;

public class PairingHeap {
    private TreeNode _root = null;

    public boolean isEmpty() {
        return null == _root;
    }

    public void add(int value) {
        if (null == search(_root, value)) {
            _root = (null == _root) ? new TreeNode(value) : merge(_root, new TreeNode(value));
        }
    }

    public void erase(int value) {
        TreeNode node = search(_root, value);
        if (null == node) {
            return;
        }

        if (value != _root.value) {
            node.value = _root.value - 1;
            decrease(node);
        }

        TreeNode current = _root;
        if (null == current.child) {
            _root = null;
        } else {
            TreeNode child = current.child;
            child.parent = null;
            _root = combine(child);
        }
    }

    public void set(int target, int value) {
        TreeNode node = search(_root, target);
        if (null != node && target != value && null == search(_root, value)) {
            node.value = value;
            if (target < value) {
                increase(node);
            } else {
                decrease(node);
            }
        }
    }

    public int getRoot() {
        if (null != _root) {
            return _root.value;
        }
        return Integer.MIN_VALUE;
    }

    public boolean contains(int value) {
        return null != search(_root, value);
    }

    public void clear() {
        _root = null;
    }

    private TreeNode merge(TreeNode node1, TreeNode node2) {
        if (null == node1 || null == node2) {
            return (null != node1) ? node1 : node2;
        }

        if (node1.value < node2.value) {
            TreeNode next = node2.next;
            node1.next = next;
            if (null != next) {
                next.parent = node1;
            }

            TreeNode child = node1.child;
            node2.parent = node1;
            node2.next = child;
            if (null != child) {
                child.parent = node2;
            }
            node1.child = node2;
            return node1;
        }

        TreeNode parent = node1.parent;
        node2.parent = parent;
        if (null != parent && parent.child != node1) {
            parent.next = node2;
        }

        TreeNode child = node2.child;
        node1.parent = node2;
        node1.next = child;
        if (null != child) {
            child.parent = node1;
        }
        node2.child = node1;
        return node2;
    }

    private TreeNode combine(TreeNode node) {
        TreeNode current = node;
        TreeNode next = current.next;
        TreeNode tail = current;

        boolean flag = true;
        while (null != next) {
            tail = merge(current, next);
            current = tail.next;
            next = (null != current) ? current.next : null;

            if (!flag && null == current) {
                break;
            }
            flag = false;
        }

        if (null != current) {
            tail = current;
        }

        TreeNode parent = tail.parent;
        while (null != parent) {
            tail = merge(parent, tail);
            parent = tail.parent;
        }
        return tail;
    }

    private TreeNode search(TreeNode node, int value) {
        while (null != node) {
            if (value == node.value) {
                return node;
            }

            TreeNode child = search(node.child, value);
            if (null != child) {
                return child;
            }
            node = node.next;
        }
        return null;
    }

    private void increase(TreeNode node) {
        int pivot = node.value;
        while (null != node.child && pivot < node.child.value) {
            node.value = node.child.value;
            node = node.child;
        }
        node.value = pivot;
    }

    private void decrease(TreeNode node) {
        TreeNode parent = node.parent;
        if (parent.child == node) {
            parent.child = node.next;
        } else {
            parent.next = node.next;
        }
        if (null != node.next) {
            node.next.parent = parent;
        }

        node.parent = null;
        node.next = null;
        _root = merge(node, _root);
    }

    private class TreeNode {
        public int value = 0;
        public TreeNode child = null;
        public TreeNode parent = null;
        public TreeNode next = null;

        public TreeNode(int value) {
            this.value = value;
        }
    }
}
