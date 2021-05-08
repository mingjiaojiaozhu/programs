package sort.linked_list;

public class RadixSort {
    public void sort(ListNode head) {
        int maxValue = head.next.value;
        int minValue = head.next.value;
        ListNode current = head.next.next;
        while (null != current) {
            if (maxValue < current.value) {
                maxValue = current.value;
            }
            if (minValue > current.value) {
                minValue = current.value;
            }
            current = current.next;
        }

        ListNode[] buckets = new ListNode[10];
        for (int i = 0; i < 10; ++i) {
            buckets[i] = new ListNode(0);
        }

        int diff = maxValue - minValue;
        for (int gap = 1; gap <= diff; gap *= 10) {
            for (ListNode bucket : buckets) {
                bucket.next = null;
            }

            current = head.next;
            while (null != current) {
                ListNode bucket = buckets[((current.value - minValue) / gap) % 10];
                while (null != bucket.next) {
                    bucket = bucket.next;
                }
                bucket.next = current;
                current = current.next;
                bucket.next.next = null;
            }

            current = head;
            for (ListNode bucket : buckets) {
                current.next = bucket.next;
                while (null != current.next) {
                    current = current.next;
                }
            }
            current.next = null;
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
