package structure.linear.linked_list;

public class SinglyLinkedList {
    private ListNode _head = new ListNode(0);

    public boolean isEmpty() {
        return null == _head.next;
    }

    public void add(int index, int value) {
        ListNode current = _head;
        int count = 0;
        while (null != current && count < index) {
            current = current.next;
            ++count;
        }

        if (null != current && count <= index) {
            ListNode node = new ListNode(value);
            node.next = current.next;
            current.next = node;
        }
    }

    public void addHead(int value) {
        ListNode node = new ListNode(value);
        node.next = _head.next;
        _head.next = node;
    }

    public void addTail(int value) {
        ListNode current = _head;
        while (null != current.next) {
            current = current.next;
        }

        ListNode node = new ListNode(value);
        node.next = null;
        current.next = node;
    }

    public void erase(int index) {
        ListNode current = _head;
        int count = 0;
        while (null != current.next && count < index) {
            current = current.next;
            ++count;
        }

        if (null != current.next && count <= index) {
            current.next = current.next.next;
        }
    }

    public void eraseHead() {
        if (null != _head.next) {
            _head.next = _head.next.next;
        }
    }

    public void eraseTail() {
        if (null == _head.next) {
            return;
        }

        ListNode current = _head;
        while (null != current.next.next) {
            current = current.next;
        }
        current.next = null;
    }

    public void set(int index, int value) {
        ListNode current = _head.next;
        int count = 0;
        while (null != current && count < index) {
            current = current.next;
            ++count;
        }

        if (null != current && count <= index) {
            current.value = value;
        }
    }

    public int get(int index) {
        ListNode current = _head.next;
        int count = 0;
        while (null != current && count < index) {
            current = current.next;
            ++count;
        }

        if (null != current && count <= index) {
            return current.value;
        }
        return Integer.MIN_VALUE;
    }

    public void reverse() {
        ListNode prev = null;
        ListNode current = _head.next;
        while (null != current) {
            ListNode next = current.next;
            current.next = prev;
            prev = current;
            current = next;
        }
        _head.next = prev;
    }

    public void clear() {
        _head.next = null;
    }

    private class ListNode {
        public int value = 0;
        public ListNode next = null;

        public ListNode(int value) {
            this.value = value;
        }
    }
}
