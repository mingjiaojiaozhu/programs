package classic.branch_and_bound;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.PriorityQueue;
import java.util.Queue;

public class OptimalLoading {
    public int[] solution(int[] weights, int target) {
        int[] aux = new int[weights.length];
        Arrays.fill(aux, 0);
        for (int i = weights.length - 1; i > 0; --i) {
            aux[i - 1] = aux[i] + weights[i];
        }

        Queue<HeapNode> queue = new PriorityQueue<>(cmp);
        int weight = 0;
        int level = 0;
        HeapNode current = null;
        while (level != weights.length) {
            if (weight + weights[level] <= target) {
                queue.offer(new HeapNode(weight + weights[level] + aux[level], level + 1, current, true));
            }
            queue.offer(new HeapNode(weight + aux[level], level + 1, current, false));

            current = queue.poll();
            level = current.level;
            weight = current.weight - aux[level - 1];
        }

        List<Integer> result = new ArrayList<>();
        for (int i = weights.length - 1; i >= 0; --i) {
            if (current.marked) {
                result.add(weights[i]);
            }
            current = current.parent;
        }
        Collections.reverse(result);
        return result.stream().mapToInt(Integer::valueOf).toArray();
    }

    private class HeapNode {
        public int weight = 0;
        public int level = 0;
        public HeapNode parent = null;
        public boolean marked = false;

        public HeapNode(int weight, int level, HeapNode parent, boolean marked) {
            this.weight = weight;
            this.level = level;
            this.parent = parent;
            this.marked = marked;
        }
    }

    private static Comparator<HeapNode> cmp = new Comparator<HeapNode>() {
        @Override
        public int compare(HeapNode node1, HeapNode node2) {
            return node2.weight - node1.weight;
        }
    };
}
