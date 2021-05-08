package structure.linear.linked_list;

public class CircularLinkedList {
    public boolean isCircular(ListNode head) {
        ListNode slow = head.next;
        ListNode fast = head.next;
        while (null != fast && null != fast.next) {
            slow = slow.next;
            fast = fast.next.next;
            if (slow == fast) {
                return true;
            }
        }
        return false;
    }

    public int circularLength(ListNode head) {
        ListNode slow = head.next;
        ListNode fast = head.next;
        while (null != fast && null != fast.next) {
            slow = slow.next;
            fast = fast.next.next;
            if (slow == fast) {
                break;
            }
        }

        if (null == fast || null == fast.next) {
            return 0;
        }

        slow = slow.next;
        int count = 1;
        while (slow != fast) {
            slow = slow.next;
            ++count;
        }
        return count;
    }

    public ListNode circularEntry(ListNode head) {
        ListNode slow = head.next;
        ListNode fast = head.next;
        while (null != fast && null != fast.next) {
            slow = slow.next;
            fast = fast.next.next;
            if (slow == fast) {
                break;
            }
        }

        if (null == fast || null == fast.next) {
            return null;
        }

        fast = head.next;
        while (slow != fast) {
            slow = slow.next;
            fast = fast.next;
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
