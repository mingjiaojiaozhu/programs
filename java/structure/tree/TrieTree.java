package structure.tree;

import java.util.Arrays;

public class TrieTree {
    private TreeNode _root = new TreeNode();

    public boolean isEmpty() {
        for (int i = 0; i < 26; ++i) {
            if (null != _root.next[i]) {
                return false;
            }
        }
        return true;
    }

    public void add(String text) {
        TreeNode current = _root;
        for (char value : text.toCharArray()) {
            int index = value - 'a';
            if (null == current.next[index]) {
                current.next[index] = new TreeNode();
                ++current.depth;
            }
            current = current.next[index];
        }
        current.ended = true;
    }

    public void erase(String text) {
        int index = text.charAt(0) - 'a';
        _root.next[index] = eraseNode(_root.next[index], text, text.length(), 1);
    }

    public boolean contains(String text) {
        TreeNode current = _root;
        for (char value : text.toCharArray()) {
            int index = value - 'a';
            TreeNode next = current.next[index];
            if (null == next) {
                return false;
            }
            current = next;
        }
        return current.ended;
    }

    public void clear() {
        for (int i = 0; i < 26; ++i) {
            _root.next[i] = null;
        }
    }

    private TreeNode eraseNode(TreeNode current, String text, int depth, int pos) {
        if (null == current) {
            return null;
        }

        if (pos >= depth) {
            if (0 == current.depth) {
                return null;
            }
            current.ended = false;
            return current;
        }

        int index = text.charAt(pos) - 'a';
        current.next[index] = eraseNode(current.next[index], text, depth, pos + 1);
        if (null != current.next[index]) {
            return current;
        }

        if (0 != current.depth) {
            --current.depth;
        }
        if (0 == current.depth && !current.ended) {
            return null;
        }
        return current;
    }

    private class TreeNode {
        public TreeNode[] next = null;
        public int depth = 0;
        public boolean ended = false;

        public TreeNode() {
            next = new TreeNode[26];
            Arrays.fill(next, null);
        }
    }
}
