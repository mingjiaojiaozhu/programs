package search.top_k;

import java.util.Comparator;
import java.util.PriorityQueue;
import java.util.Queue;

public class HeapSelect {
    public int[] search(int[] nums, int k) {
        Queue<Integer> queue = new PriorityQueue<>(cmp);
        for (int value : nums) {
            if (queue.size() < k) {
                queue.offer(value);
                continue;
            }

            if (value < queue.peek()) {
                queue.poll();
                queue.offer(value);
            }
        }
        return queue.stream().mapToInt(Integer::valueOf).toArray();
    }

    private static Comparator<Integer> cmp = new Comparator<Integer>() {
        @Override
        public int compare(Integer i, Integer j) {
            return j - i;
        }
    };
}
