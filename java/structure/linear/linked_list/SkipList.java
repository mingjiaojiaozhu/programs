package structure.linear.linked_list;

import java.util.Arrays;
import java.util.Random;

public class SkipList {
    private static final Random _random = new Random();

    private ListNode _head = new ListNode(0);
    private int _maxLevel = 1;

    public boolean isEmpty() {
        return null == _head.next[0];
    }

    public void add(int value) {
        int num = _random.nextInt(65536);
        int level = 0;
        while (0 != num) {
            ++level;
            num &= num - 1;
        }

        ListNode[] next = new ListNode[level];
        Arrays.fill(next, _head);
        for (int i = level - 1; i >= 0; --i) {
            ListNode current = _head;
            while (null != current.next[i] && value > current.next[i].value) {
                current = current.next[i];
            }

            if (null != current.next[i] && value == current.next[i].value) {
                return;
            }
            next[i] = current;
        }

        ListNode node = new ListNode(value);
        for (int i = 0; i < level; ++i) {
            node.next[i] = next[i].next[i];
            next[i].next[i] = node;
        }

        if (_maxLevel < level) {
            _maxLevel = level;
        }
    }

    public void erase(int value) {
        ListNode[] next = new ListNode[_maxLevel];
        ListNode current = _head;
        for (int i = _maxLevel - 1; i >= 0; --i) {
            while (null != current.next[i] && value > current.next[i].value) {
                current = current.next[i];
            }
            next[i] = current;
        }

        if (null == current.next[0] || value != current.next[0].value) {
            return;
        }

        for (int i = _maxLevel - 1; i >= 0; --i) {
            if (null != next[i].next[i] && value == next[i].next[i].value) {
                next[i].next[i] = next[i].next[i].next[i];
            }
        }

        for (int i = _maxLevel - 1; i >= 0; --i) {
            if (null != _head.next[i]) {
                break;
            }
            --_maxLevel;
        }
    }

    public boolean contains(int value) {
        ListNode current = _head;
        for (int i = _maxLevel - 1; i >= 0; --i) {
            while (null != current.next[i] && value > current.next[i].value) {
                current = current.next[i];
            }
        }
        return null != current.next[0] && value == current.next[0].value;
    }

    public void clear() {
        Arrays.fill(_head.next, null);
        _maxLevel = 1;
    }

    private class ListNode {
        public int value = 0;
        public ListNode next[] = null;

        public ListNode(int value) {
            this.value = value;
            next = new ListNode[16];
            Arrays.fill(next, null);
        }
    }
}
