package structure.linear.queue;

public class QueueOfLinkedList {
    private ListNode _head = new ListNode(0);
    private ListNode _tail = new ListNode(0);

    public QueueOfLinkedList() {
        _head.next = _tail;
        _tail.prev = _head;
    }

    public boolean isEmpty() {
        return _head.next == _tail;
    }

    public void enqueue(int value) {
        ListNode node = new ListNode(value);
        node.prev = _tail.prev;
        node.next = _tail;
        _tail.prev.next = node;
        _tail.prev = node;
    }

    public int dequeue() {
        if (_head.next != _tail) {
            ListNode node = _head.next;
            node.next.prev = _head;
            _head.next = node.next;
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
