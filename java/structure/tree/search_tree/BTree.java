package structure.tree.search_tree;

import java.util.Arrays;

public class BTree {
    private TreeNode _root = null;
    private int _degree = 0;

    public BTree(int degree) {
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
            ++_root.count;
            return;
        }

        if (_root.count != (_degree << 1) - 1) {
            addNode(_root, key, value);
            return;
        }

        TreeNode node = new TreeNode(_degree, false);
        node.children[0] = _root;
        splitChild(node, _root, 0);

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
            _root = _root.leaf ? null : _root.children[0];
        }
    }

    public void set(int key, int value) {
        TreeNode current = _root;
        while (null != current) {
            int start = 0;
            int end = current.count - 1;
            while (start <= end) {
                int middle = start + ((end - start) >> 1);
                if (key == current.keys[middle]) {
                    current.values[middle] = value;
                    return;
                }

                if (key < current.keys[middle]) {
                    end = middle - 1;
                } else {
                    start = middle + 1;
                }
            }

            if (current.leaf) {
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
                if (key == current.keys[middle]) {
                    return current.values[middle];
                }

                if (key < current.keys[middle]) {
                    end = middle - 1;
                } else {
                    start = middle + 1;
                }
            }

            if (current.leaf) {
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
            if (key == parent.keys[middle]) {
                parent.values[middle] = value;
                return;
            }

            if (key < parent.keys[middle]) {
                end = middle - 1;
            } else {
                start = middle + 1;
            }
        }

        if (parent.leaf) {
            for (int i = parent.count - 1; i > end; --i) {
                parent.keys[i + 1] = parent.keys[i];
                parent.values[i + 1] = parent.values[i];
            }
            parent.keys[end + 1] = key;
            parent.values[end + 1] = value;
            ++parent.count;
            return;
        }

        if (parent.children[end + 1].count == (_degree << 1) - 1) {
            splitChild(parent, parent.children[end + 1], end + 1);
            if (parent.keys[end + 1] < key) {
                ++end;
            }
        }
        addNode(parent.children[end + 1], key, value);
    }

    private void eraseNode(TreeNode parent, int key) {
        int start = 0;
        int end = parent.count - 1;
        boolean exists = false;
        while (start <= end) {
            int middle = start + ((end - start) >> 1);
            if (key == parent.keys[middle]) {
                exists = true;
                break;
            }

            if (key < parent.keys[middle]) {
                end = middle - 1;
            } else {
                start = middle + 1;
            }
        }

        if (!exists) {
            if (parent.leaf) {
                return;
            }

            boolean flag = (start == parent.count);
            if (parent.children[start].count < _degree) {
                fillChild(parent, start);
            }

            if (flag && start > parent.count) {
                eraseNode(parent.children[start - 1], key);
            } else {
                eraseNode(parent.children[start], key);
            }
            return;
        }

        if (parent.leaf) {
            for (int i = start + 1; i < parent.count; ++i) {
                parent.keys[i - 1] = parent.keys[i];
                parent.values[i - 1] = parent.values[i];
            }
            --parent.count;
            return;
        }

        if (parent.children[start].count >= _degree) {
            TreeNode current = parent.children[start];
            while (!current.leaf) {
                current = current.children[current.count];
            }

            parent.keys[start] = current.keys[current.count - 1];
            parent.values[start] = current.values[current.count - 1];
            eraseNode(parent.children[start], current.keys[current.count - 1]);
            return;
        }

        if (parent.children[start + 1].count >= _degree) {
            TreeNode current = parent.children[start + 1];
            while (!current.leaf) {
                current = current.children[0];
            }

            parent.keys[start] = current.keys[0];
            parent.values[start] = current.values[0];
            eraseNode(parent.children[start + 1], current.keys[0]);
            return;
        }

        mergeChild(parent, start);
        eraseNode(parent.children[start], key);
    }

    private void splitChild(TreeNode parent, TreeNode child, int index) {
        TreeNode node = new TreeNode(_degree, child.leaf);
        System.arraycopy(child.keys, _degree, node.keys, 0, child.count - _degree);
        System.arraycopy(child.values, _degree, node.values, 0, child.count - _degree);
        if (!child.leaf) {
            System.arraycopy(child.children, _degree, node.children, 0, child.count - _degree + 1);
        }

        for (int i = parent.count - 1; i >= index; --i) {
            parent.keys[i + 1] = parent.keys[i];
            parent.values[i + 1] = parent.values[i];
        }
        for (int i = parent.count; i > index; --i) {
            parent.children[i + 1] = parent.children[i];
        }
        parent.keys[index] = child.keys[_degree - 1];
        parent.values[index] = child.values[_degree - 1];
        parent.children[index + 1] = node;

        node.count = _degree - 1;
        child.count = _degree - 1;
        ++parent.count;
    }

    private void fillChild(TreeNode parent, int index) {
        if (0 != index && parent.children[index - 1].count >= _degree) {
            borrowFromPrev(parent, index);
            return;
        }

        if (index != parent.count && parent.children[index + 1].count >= _degree) {
            borrowFromNext(parent, index);
            return;
        }

        if (index != parent.count) {
            mergeChild(parent, index);
        } else {
            mergeChild(parent, index - 1);
        }
    }

    private void mergeChild(TreeNode parent, int index) {
        TreeNode child = parent.children[index];
        TreeNode node = parent.children[index + 1];

        child.keys[_degree - 1] = parent.keys[index];
        child.values[_degree - 1] = parent.values[index];
        System.arraycopy(node.keys, 0, child.keys, _degree, node.count);
        System.arraycopy(node.values, 0, child.values, _degree, node.count);
        if (!child.leaf) {
            System.arraycopy(node.children, 0, child.children, _degree, node.count + 1);
        }

        for (int i = index + 1; i < parent.count; ++i) {
            parent.keys[i - 1] = parent.keys[i];
            parent.values[i - 1] = parent.values[i];
        }
        for (int i = index + 2; i <= parent.count; ++i) {
            parent.children[i - 1] = parent.children[i];
        }

        child.count += node.count + 1;
        --parent.count;
    }

    private void borrowFromPrev(TreeNode parent, int index) {
        TreeNode child = parent.children[index];
        TreeNode node = parent.children[index - 1];

        for (int i = child.count - 1; i >= 0; --i) {
            child.keys[i + 1] = child.keys[i];
            child.values[i + 1] = child.values[i];
        }
        child.keys[0] = parent.keys[index - 1];
        child.values[0] = parent.values[index - 1];
        if (!child.leaf) {
            for (int i = child.count; i >= 0; --i) {
                child.children[i + 1] = child.children[i];
            }
            child.children[0] = node.children[node.count];
        }

        parent.keys[index - 1] = node.keys[node.count - 1];
        parent.values[index - 1] = node.values[node.count - 1];

        ++child.count;
        --node.count;
    }

    private void borrowFromNext(TreeNode parent, int index) {
        TreeNode child = parent.children[index];
        TreeNode node = parent.children[index + 1];

        child.keys[child.count] = parent.keys[index];
        child.values[child.count] = parent.values[index];
        if (!child.leaf) {
            child.children[child.count + 1] = node.children[0];
        }

        parent.keys[index] = node.keys[0];
        parent.values[index] = node.values[0];

        for (int i = 1; i < node.count; ++i) {
            node.keys[i - 1] = node.keys[i];
            node.values[i - 1] = node.values[i];
        }
        if (!node.leaf) {
            for (int i = 1; i <= node.count; ++i) {
                node.children[i - 1] = node.children[i];
            }
        }

        ++child.count;
        --node.count;
    }

    private class TreeNode {
        public int[] keys = null;
        public int[] values = null;
        public TreeNode[] children = null;
        public int count = 0;
        public boolean leaf = false;

        public TreeNode(int degree, boolean leaf) {
            keys = new int[(degree << 1) - 1];
            Arrays.fill(keys, 0);
            values = new int[(degree << 1) - 1];
            Arrays.fill(values, 0);
            if (!leaf) {
                children = new TreeNode[degree << 1];
                Arrays.fill(children, null);
            }
            this.leaf = leaf;
        }
    }
}
