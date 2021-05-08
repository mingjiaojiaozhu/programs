package sort.linked_list;

public class MergeSort {
    public void sort(ListNode head) {
        sort(head, head.next);
    }

    private void sort(ListNode head, ListNode start) {
        if (null == start.next) {
            head.next = start;
            return;
        }

        ListNode left = new ListNode(0);
        ListNode right = new ListNode(0);
        ListNode middle = getMiddle(start);
        left.next = start;
        right.next = middle.next;
        middle.next = null;

        sort(left, left.next);
        sort(right, right.next);
        merge(head, left.next, right.next);
    }

    private void merge(ListNode head, ListNode left, ListNode right) {
        ListNode current = head;
        while (null != left && null != right) {
            if (left.value > right.value) {
                current.next = right;
                right = right.next;
            } else {
                current.next = left;
                left = left.next;
            }
            current = current.next;
        }

        if (null != left) {
            current.next = left;
        }
        if (null != right) {
            current.next = right;
        }
    }

    private ListNode getMiddle(ListNode start) {
        if (null == start.next) {
            return start;
        }

        ListNode slow = start;
        ListNode fast = start.next;
        while (null != fast && null != fast.next) {
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
