package sort.linked_list;

public class BubbleSort {
    public void sort(ListNode head) {
        ListNode border = null;
        while (head.next.next != border) {
            boolean flag = false;
            ListNode prev = head;
            ListNode current = head.next;
            while (current.next != border) {
                if (current.value > current.next.value) {
                    ListNode next = current.next;
                    current.next = next.next;
                    next.next = prev.next;
                    prev.next = next;

                    flag = true;
                    current = prev.next;
                }
                prev = prev.next;
                current = current.next;
            }
            border = current;

            if (!flag) {
                break;
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
