package structure.linear.stack;

public class StackOfLinkedList {
    private ListNode _head = new ListNode(0);

    public boolean isEmpty() {
        return null == _head.next;
    }

    public void push(int value) {
        ListNode node = new ListNode(value);
        node.next = _head.next;
        _head.next = node;
    }

    public int pop() {
        if (null != _head.next) {
            ListNode node = _head.next;
            _head.next = node.next;
            return node.value;
        }
        return Integer.MIN_VALUE;
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
