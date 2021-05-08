package structure.linear.linked_list;

public class DoublyLinkedList {
    private ListNode _head = new ListNode(0);
    private ListNode _tail = new ListNode(0);

    public DoublyLinkedList() {
        _head.next = _tail;
        _tail.prev = _head;
    }

    public boolean isEmpty() {
        return _head.next == _tail;
    }

    public void add(int index, int value) {
        ListNode current = _head;
        int count = 0;
        while (current != _tail && count < index) {
            current = current.next;
            ++count;
        }

        if (current != _tail && count <= index) {
            ListNode node = new ListNode(value);
            node.next = current.next;
            node.prev = current;
            current.next.prev = node;
            current.next = node;
        }
    }

    public void addHead(int value) {
        ListNode node = new ListNode(value);
        node.next = _head.next;
        node.prev = _head;
        _head.next.prev = node;
        _head.next = node;
    }

    public void addTail(int value) {
        ListNode node = new ListNode(value);
        node.prev = _tail.prev;
        node.next = _tail;
        _tail.prev.next = node;
        _tail.prev = node;
    }

    public void erase(int index) {
        ListNode current = _head;
        int count = 0;
        while (current.next != _tail && count < index) {
            current = current.next;
            ++count;
        }

        if (current.next != _tail && count <= index) {
            current.next.next.prev = current;
            current.next = current.next.next;
        }
    }

    public void eraseHead() {
        if (_head.next != _tail) {
            _head.next.next.prev = _head;
            _head.next = _head.next.next;
        }
    }

    public void eraseTail() {
        if (_head.next != _tail) {
            _tail.prev.prev.next = _tail;
            _tail.prev = _tail.prev.prev;
        }
    }

    public void set(int index, int value) {
        ListNode current = _head.next;
        int count = 0;
        while (current != _tail && count < index) {
            current = current.next;
            ++count;
        }

        if (current != _tail && count <= index) {
            current.value = value;
        }
    }

    public int get(int index) {
        ListNode current = _head.next;
        int count = 0;
        while (current != _tail && count < index) {
            current = current.next;
            ++count;
        }

        if (current != _tail && count <= index) {
            return current.value;
        }
        return Integer.MIN_VALUE;
    }

    public void clear() {
        _head.next = _tail;
        _tail.prev = _head;
    }

    private class ListNode {
        public int value = 0;
        public ListNode prev = null;
        public ListNode next = null;

        public ListNode(int value) {
            this.value = value;
        }
    }
}
