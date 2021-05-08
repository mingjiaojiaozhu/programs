package sort.linked_list;

public class SelectionSort {
    public void sort(ListNode head) {
        ListNode prev = head;
        while (null != prev.next) {
            ListNode current = prev;
            for (ListNode node = prev.next; null != node.next; node = node.next) {
                if (current.next.value > node.next.value) {
                    current = node;
                }
            }

            if (prev != current) {
                ListNode next = current.next;
                current.next = next.next;
                next.next = prev.next;
                prev.next = next;
            }
            prev = prev.next;
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
