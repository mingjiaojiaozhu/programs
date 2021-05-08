package sort.linked_list;

public class InsertionSort {
    public void sort(ListNode head) {
        ListNode current = head.next;
        while (null != current.next) {
            ListNode prev = head;
            while (prev != current && prev.next.value <= current.next.value) {
                prev = prev.next;
            }

            if (prev == current) {
                current = current.next;
            } else {
                ListNode next = current.next;
                current.next = next.next;
                next.next = prev.next;
                prev.next = next;
            }
        }
    }

    public class ListNode {
        public int value = 0;
        public ListNode next = null;

        public ListNode(int value) {
            this.value = value;
        }
    }
}
