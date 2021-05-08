package structure.tree.heap;

public class BinomialHeap {
    private TreeNode _root = null;

    public boolean isEmpty() {
        return null == _root;
    }

    public void add(int value) {
        if (null == search(_root, value)) {
            _root = (null == _root) ? new TreeNode(value) : combine(_root, new TreeNode(value));
        }
    }

    public void erase(int value) {
        TreeNode node = search(_root, value);
        if (null == node) {
            return;
        }

        TreeNode parent = node.parent;
        while (null != parent) {
            swap(node, parent);

            node = parent;
            parent = node.parent;
        }

        TreeNode pivot = null;
        TreeNode current = _root;
        while (current != node) {
            pivot = current;
            current = current.next;
        }

        if (null != pivot) {
            pivot.next = node.next;
        } else {
            _root = node.next;
        }
        _root = combine(_root, reverse(node.child));
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
        if (null == _root) {
            return Integer.MIN_VALUE;
        }

        TreeNode pivot = _root;
        TreeNode current = _root.next;
        while (null != current) {
            if (pivot.value > current.value) {
                pivot = current;
            }
            current = current.next;
        }
        return pivot.value;
    }

    public boolean contains(int value) {
        return null != search(_root, value);
    }

    public void clear() {
        _root = null;
    }

    private TreeNode combine(TreeNode node1, TreeNode node2) {
        TreeNode head = merge(node1, node2);
        if (null == head) {
            return head;
        }

        TreeNode parent = null;
        TreeNode current = head;
        while (null != current.next) {
            TreeNode next = current.next;
            if ((current.degree != next.degree) || (null != next.next && next.degree == next.next.degree)) {
                parent = current;
                current = next;
            } else if (current.value <= next.value) {
                current.next = next.next;
                link(current, next);
            } else {
                if (null == parent) {
                    head = next;
                } else {
                    parent.next = next;
                }
                link(next, current);
                current = next;
            }
        }
        return head;
    }

    private TreeNode merge(TreeNode node1, TreeNode node2) {
        if (null == node1 || null == node2) {
            return (null != node1) ? node1 : node2;
        }

        TreeNode parent = null;
        TreeNode head = null;
        while (null != node1 && null != node2) {
            TreeNode pivot = null;
            if (node1.degree <= node2.degree) {
                pivot = node1;
                node1 = node1.next;
            } else {
                pivot = node2;
                node2 = node2.next;
            }

            if (null == parent) {
                parent = pivot;
                head = pivot;
            } else {
                parent.next = pivot;
                parent = pivot;
            }
            pivot.next = (null != node1) ? node1: node2;
        }
        return head;
    }

    private TreeNode reverse(TreeNode node) {
        if (null == node) {
            return node;
        }

        node.parent = null;
        TreeNode tail = null;
        while (null != node.next) {
            TreeNode next = node.next;
            node.next = tail;
            tail = node;
            node = next;
            node.parent = null;
        }
        node.next = tail;
        return node;
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
        TreeNode child = node.child;
        while (null != child) {
            if (node.value < child.value) {
                child = child.next;
                continue;
            }

            TreeNode pivot = child;
            while (null != child.next) {
                if (child.next.value < pivot.value) {
                    pivot = child.next;
                }
                child = child.next;
            }
            swap(node, pivot);

            node = pivot;
            child = node.child;
        }
    }

    private void decrease(TreeNode node) {
        TreeNode parent = node.parent;
        while (null != parent && node.value < parent.value) {
            swap(node, parent);

            node = parent;
            parent = node.parent;
        }
    }

    private void link(TreeNode parent, TreeNode child) {
        child.parent = parent;
        child.next = parent.child;
        parent.child = child;
        ++parent.degree;
    }

    private void swap(TreeNode p, TreeNode q) {
        p.value ^= q.value;
        q.value ^= p.value;
        p.value ^= q.value;
    }

    private class TreeNode {
        public int value = 0;
        public int degree = 0;
        public TreeNode child = null;
        public TreeNode parent = null;
        public TreeNode next = null;

        public TreeNode(int value) {
            this.value = value;
        }
    }
}
