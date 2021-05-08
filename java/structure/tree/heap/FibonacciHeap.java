package structure.tree.heap;

import java.util.Arrays;

public class FibonacciHeap {
    private TreeNode _root = null;
    private int _length = 0;

    public boolean isEmpty() {
        return null == _root;
    }

    public void add(int value) {
        if (null != search(_root, value)) {
            return;
        }

        if (null == _root) {
            _root = new TreeNode(value);
            _root.left = _root;
            _root.right = _root;
        } else {
            TreeNode node = new TreeNode(value);
            addNode(node, _root);
            if (value < _root.value) {
                _root = node;
            }
        }
        ++_length;
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
        while (null != current.child) {
            TreeNode child = current.child;
            eraseNode(child);
            current.child = (child.right != child) ? child.right : null;
            addNode(child, _root);
            child.parent = null;
        }

        eraseNode(current);
        _root = (current.right != current) ? current.right : null;
        if (current.right != current) {
            combine();
        }
        --_length;
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
        _length = 0;
    }

    private void combine() {
        int maxDegree = (int) Math.ceil(Math.log(_length) / Math.log(2));
        TreeNode[] heads = new TreeNode[maxDegree + 1];
        Arrays.fill(heads, null);

        while (null != _root) {
            TreeNode current = _root;
            if (current == current.right) {
                _root = null;
            } else {
                eraseNode(current);
                _root = current.right;
            }
            current.left = current;
            current.right = current;

            int degree = current.degree;
            while (null != heads[degree]) {
                TreeNode node = heads[degree];
                if (current.value > node.value) {
                    TreeNode aux = current;
                    current = node;
                    node = aux;
                }

                link(node, current);
                heads[degree] = null;
                ++degree;
            }
            heads[degree] = current;
        }

        for (TreeNode head : heads) {
            if (null == head) {
                continue;
            }

            if (null == _root) {
                _root = head;
            } else {
                addNode(head, _root);
                if (head.value < _root.value) {
                    _root = head;
                }
            }
        }
    }

    private TreeNode search(TreeNode node, int value) {
        if (null == node) {
            return null;
        }

        TreeNode current = node;
        boolean flag = true;
        while (flag || current != node) {
            flag = false;
            if (current.value == value) {
                return current;
            }

            TreeNode child = search(current.child, value);
            if (null != child) {
                return child;
            }
            current = current.right;
        }
        return null;
    }

    private void increase(TreeNode node) {
        while (null != node.child) {
            TreeNode child = node.child;
            eraseNode(child);
            if (child.right == child) {
                node.child = null;
            } else {
                node.child = child.right;
            }

            addNode(child, _root);
            child.parent = null;
        }
        node.degree = 0;

        TreeNode parent = node.parent;
        if (null != parent) {
            cut(node, parent);
            cascadingCut(parent);
        } else if (_root == node) {
            TreeNode right = node.right;
            while (right != node) {
                if (node.value > right.value) {
                    _root = right;
                }
                right = right.right;
            }
        }
    }

    private void decrease(TreeNode node) {
        TreeNode parent = node.parent;
        if (null != parent && node.value < parent.value) {
            cut(node, parent);
            cascadingCut(parent);
        }

        if (node.value < _root.value) {
            _root = node;
        }
    }

    private void link(TreeNode parent, TreeNode child) {
        eraseNode(parent);
        if (null == child.child) {
            child.child = parent;
        } else {
            addNode(parent, child.child);
        }

        parent.parent = child;
        parent.marked = false;
        ++child.degree;
    }

    private void addNode(TreeNode node1, TreeNode node2) {
        node2.left.right = node1;
        node1.left = node2.left;
        node1.right = node2;
        node2.left = node1;
    }

    private void eraseNode(TreeNode node) {
        node.left.right = node.right;
        node.right.left = node.left;
    }

    private void cut(TreeNode node, TreeNode parent) {
        eraseNode(node);
        setDegree(parent, node.degree);
        parent.child = (node != node.right) ? node.right : null;

        node.parent = null;
        node.left = node;
        node.right = node;
        node.marked = false;
        addNode(node, _root);
    }

    private void cascadingCut(TreeNode node) {
        TreeNode parent = node.parent;
        if (null != parent) {
            if (!node.marked) {
                node.marked = true;
            } else {
                cut(node, parent);
                cascadingCut(parent);
            }
        }
    }

    private void setDegree(TreeNode parent, int degree) {
        parent.degree -= degree;
        if (null != parent.parent) {
            setDegree(parent.parent, degree);
        }
    }

    private class TreeNode {
        public int value = 0;
        public int degree = 0;
        public TreeNode child = null;
        public TreeNode parent = null;
        public TreeNode left = null;
        public TreeNode right = null;
        public boolean marked = false;

        public TreeNode(int value) {
            this.value = value;
        }
    }
}
