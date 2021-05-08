package search.linked_list;

public class BinarySearch {
    public ListNode search(ListNode head, int target) {
        return search(head.next, null, target);
    }

    private ListNode search(ListNode start, ListNode end, int target) {
        if (start == end) {
            return (null != start && target == start.value) ? start : null;
        }

        ListNode middle = getMiddle(start, end);
        if (target == middle.value) {
            return middle;
        }

        if (target < middle.value) {
            return search(start, middle, target);
        }
        return search(middle.next, null, target);
    }

    private ListNode getMiddle(ListNode start, ListNode end) {
        ListNode slow = start;
        ListNode fast = start.next;
        while (fast != end && fast.next != end) {
            slow = slow.next;
            fast = fast.next.next;
        }
        return slow;
    }

    public class ListNode {
        public int value = 0;
        public ListNode next = null;

        public ListNode(int value) {
            this.value = value;
        }
    }
}
