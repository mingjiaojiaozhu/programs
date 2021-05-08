package structure.tree.search_tree;

import java.util.Arrays;

public class BPlusTree {
    private TreeNode _root = null;
    private int _degree = 0;

    public BPlusTree(int degree) {
        _degree = degree;
    }

    public boolean isEmpty() {
        return null == _root;
    }

    public void add(int key, int value) {
        if (null == _root) {
            _root = new TreeNode(_degree, true);
            _root.keys[0] = key;
            _root.values[0] = value;
            return;
        }

        if (_root.count != (_degree << 1)) {
            addNode(_root, key, value);
            return;
        }

        TreeNode node = new TreeNode(_degree, false);
        node.children[0] = _root;
        splitChild(node, _root, 0);

        if (key > node.keys[node.count - 1]) {
            node.keys[node.count - 1] = key;
        }

        int index = (node.keys[0] < key) ? 1 : 0;
        addNode(node.children[index], key, value);
        _root = node;
    }

    public void erase(int key) {
        if (null == _root) {
            return;
        }

        eraseNode(_root, key);
        if (0 == _root.count) {
            _root = null;
        } else if (_root.count <= 1 && !_root.leaf) {
            _root = _root.children[0];
        }
    }

    public void set(int key, int value) {
        TreeNode current = _root;
        while (null != current) {
            int start = 0;
            int end = current.count - 1;
            while (start <= end) {
                int middle = start + ((end - start) >> 1);
                if (key > current.keys[middle]) {
                    start = middle + 1;
                } else {
                    end = middle - 1;
                }
            }

            if (current.leaf) {
                if (start < current.count && key == current.keys[start]) {
                    current.values[start] = value;
                }
                return;
            }

            if (start >= current.count) {
                return;
            }
            current = current.children[start];
        }
    }

    public int get(int key) {
        TreeNode current = _root;
        while (null != current) {
            int start = 0;
            int end = current.count - 1;
            while (start <= end) {
                int middle = start + ((end - start) >> 1);
                if (key > current.keys[middle]) {
                    start = middle + 1;
                } else {
                    end = middle - 1;
                }
            }

            if (current.leaf) {
                if (start < current.count && key == current.keys[start]) {
                    return current.values[start];
                }
                return Integer.MIN_VALUE;
            }

            if (start >= current.count) {
                return Integer.MIN_VALUE;
            }
            current = current.children[start];
        }
        return Integer.MIN_VALUE;
    }

    public void clear() {
        _root = null;
    }

    private void addNode(TreeNode parent, int key, int value) {
        int start = 0;
        int end = parent.count - 1;
        while (start <= end) {
            int middle = start + ((end - start) >> 1);
            if (key > parent.keys[middle]) {
                start = middle + 1;
            } else {
                end = middle - 1;
            }
        }

        if (parent.leaf) {
            if (start < parent.count && key == parent.keys[start]) {
                parent.values[start] = value;
                return;
            }

            for (int i = parent.count - 1; i >= start; --i) {
                parent.keys[i + 1] = parent.keys[i];
                parent.values[i + 1] = parent.values[i];
            }
            parent.keys[start] = key;
            parent.values[start] = value;
            ++parent.count;
            return;
        }

        if (start >= parent.count) {
            start = parent.count - 1;
        }

        if (parent.children[start].count == (_degree << 1)) {
            splitChild(parent, parent.children[start], start);
            if (parent.keys[start] < key) {
                ++start;
            }
        }

        if (key > parent.keys[parent.count - 1]) {
            parent.keys[parent.count - 1] = key;
        }
        addNode(parent.children[start], key, value);
    }

    private void eraseNode(TreeNode parent, int key) {
        int start = 0;
        int end = parent.count - 1;
        while (start <= end) {
            int middle = start + ((end - start) >> 1);
            if (key > parent.keys[middle]) {
                start = middle + 1;
            } else {
                end = middle - 1;
            }
        }

        if (parent.leaf) {
            if (key != parent.keys[start]) {
                return;
            }

            for (int i = start + 1; i < parent.count; ++i) {
                parent.keys[i - 1] = parent.keys[i];
                parent.values[i - 1] = parent.values[i];
            }
            --parent.count;
            return;
        }

        boolean flag = (start == parent.count - 1);
        if (parent.children[start].count <= _degree) {
            fillChild(parent, start);
        }

        if (flag && start > parent.count - 1) {
            eraseNode(parent.children[start - 1], key);
        } else {
            eraseNode(parent.children[start], key);
        }

        if (key == parent.keys[parent.count - 1]) {
            parent.keys[parent.count - 1] = parent.children[parent.count - 1].keys[parent.children[parent.count - 1].count - 1];
        }
    }

    private void splitChild(TreeNode parent, TreeNode child, int index) {
        TreeNode node = new TreeNode(_degree, child.leaf);
        System.arraycopy(child.keys, _degree, node.keys, 0, child.count - _degree);
        if (child.leaf) {
            System.arraycopy(child.values, _degree, node.values, 0, child.count - _degree);

            node.next = child.next;
            child.next = node;
        } else {
            System.arraycopy(child.children, _degree, node.children, 0, child.count - _degree);
        }

        for (int i = parent.count - 1; i > index; --i) {
            parent.keys[i + 1] = parent.keys[i];
            parent.children[i + 1] = parent.children[i];
        }
        parent.keys[index] = child.keys[_degree - 1];
        parent.keys[index + 1] = node.keys[_degree - 1];
        parent.children[index + 1] = node;

        node.count = _degree;
        child.count = _degree;
        ++parent.count;
    }

    private void fillChild(TreeNode parent, int index) {
        if (0 != index && parent.children[index - 1].count > _degree) {
            borrowFromPrev(parent, index);
            return;
        }

        if (index != parent.count - 1 && parent.children[index + 1].count > _degree) {
            borrowFromNext(parent, index);
            return;
        }

        if (index != parent.count - 1) {
            mergeChild(parent, index);
        } else {
            mergeChild(parent, index - 1);
        }
    }

    private void mergeChild(TreeNode parent, int index) {
        TreeNode child = parent.children[index];
        TreeNode node = parent.children[index + 1];

        System.arraycopy(node.keys, 0, child.keys, _degree, node.count);
        if (child.leaf) {
            System.arraycopy(node.values, 0, child.values, _degree, node.count);
            child.next = node.next;
        } else {
            System.arraycopy(node.children, 0, child.children, _degree, node.count);
        }

        parent.keys[index] = node.keys[node.count - 1];
        for (int i = index + 2; i < parent.count; ++i) {
            parent.keys[i - 1] = parent.keys[i];
            parent.children[i - 1] = parent.children[i];
        }

        child.count += node.count;
        --parent.count;
    }

    private void borrowFromPrev(TreeNode parent, int index) {
        TreeNode child = parent.children[index];
        TreeNode node = parent.children[index - 1];

        for (int i = child.count - 1; i >= 0; --i) {
            child.keys[i + 1] = child.keys[i];
        }
        child.keys[0] = node.keys[node.count - 1];
        if (child.leaf) {
            for (int i = child.count - 1; i >= 0; --i) {
                child.values[i + 1] = child.values[i];
            }
            child.values[0] = node.values[node.count - 1];
        } else {
            for (int i = child.count - 1; i >= 0; --i) {
                child.children[i + 1] = child.children[i];
            }
            child.children[0] = node.children[node.count - 1];
        }

        parent.keys[index - 1] = node.keys[node.count - 2];

        ++child.count;
        --node.count;
    }

    private void borrowFromNext(TreeNode parent, int index) {
        TreeNode child = parent.children[index];
        TreeNode node = parent.children[index + 1];

        child.keys[child.count] = node.keys[0];
        if (child.leaf) {
            child.values[child.count] = node.values[0];
        } else {
            child.children[child.count] = node.children[0];
        }

        for (int i = 1; i < node.count; ++i) {
            node.keys[i - 1] = node.keys[i];
        }
        if (node.leaf) {
            for (int i = 1; i < node.count; ++i) {
                node.values[i - 1] = node.values[i];
            }
        } else {
            for (int i = 1; i < node.count; ++i) {
                node.children[i - 1] = node.children[i];
            }
        }

        parent.keys[index] = child.keys[child.count];

        ++child.count;
        --node.count;
    }

    private class TreeNode {
        public int[] keys = null;
        public int[] values = null;
        public TreeNode[] children = null;
        public int count = 1;
        public boolean leaf = false;
        public TreeNode next = null;

        public TreeNode(int degree, boolean leaf) {
            keys = new int[degree << 1];
            Arrays.fill(keys, 0);
            if (leaf) {
                values = new int[degree << 1];
                Arrays.fill(values, 0);
            } else {
                children = new TreeNode[degree << 1];
                Arrays.fill(children, null);
            }
            this.leaf = leaf;
        }
    }
}
