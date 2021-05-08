package search.linked_list;

public class SequenceSearch {
    public ListNode search(ListNode head, int target) {
        ListNode current = head.next;
        while (null != current) {
            if (target == current.value) {
                return current;
            }
            current = current.next;
        }
        return null;
    }

    public class ListNode {
        public int value = 0;
        public ListNode next = null;

        public ListNode(int value) {
            this.value = value;
        }
    }
}
