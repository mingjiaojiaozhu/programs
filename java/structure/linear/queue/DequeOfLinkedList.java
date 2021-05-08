package structure.linear.queue;

public class DequeOfLinkedList {
    private ListNode _head = new ListNode(0);
    private ListNode _tail = new ListNode(0);

    public DequeOfLinkedList() {
        _head.next = _tail;
        _tail.prev = _head;
    }

    public boolean isEmpty() {
        return _head.next == _tail;
    }

    public void enqueueHead(int value) {
        ListNode node = new ListNode(value);
        node.next = _head.next;
        node.prev = _head;
        _head.next.prev = node;
        _head.next = node;
    }

    public void enqueueTail(int value) {
        ListNode node = new ListNode(value);
        node.prev = _tail.prev;
        node.next = _tail;
        _tail.prev.next = node;
        _tail.prev = node;
    }

    public int dequeueHead() {
        if (_head.next != _tail) {
            ListNode node = _head.next;
            node.next.prev = _head;
            _head.next = node.next;
            return node.value;
        }
        return Integer.MIN_VALUE;
    }

    public int dequeueTail() {
        if (_head.next != _tail) {
            ListNode node = _tail.prev;
            node.prev.next = _tail;
            _tail.prev = node.prev;
            return node.value;
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
