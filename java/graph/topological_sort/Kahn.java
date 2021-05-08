package graph.topological_sort;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;

public class Kahn {
    public int[] sort(VertexNode[] graphs) {
        int[] inDegrees = new int[graphs.length];
        Arrays.fill(inDegrees, 0);
        for (VertexNode graph : graphs) {
            EdgeNode edge = graph.next;
            while (null != edge) {
                ++inDegrees[edge.index];
                edge = edge.next;
            }
        }

        Queue<Integer> queue = new LinkedList<>();
        for (int i = 0; i < graphs.length; ++i) {
            if (0 == inDegrees[i]) {
                queue.offer(i);
            }
        }

        List<Integer> result = new ArrayList<>();
        while (!queue.isEmpty()) {
            int index = queue.poll();
            result.add(index);

            EdgeNode edge = graphs[index].next;
            while (null != edge) {
                int edgeIndex = edge.index;
                --inDegrees[edgeIndex];
                if (0 == inDegrees[edgeIndex]) {
                    queue.offer(edgeIndex);
                }
                edge = edge.next;
            }
        }
        return (result.size() == graphs.length) ? result.stream().mapToInt(Integer::valueOf).toArray() : new int[0];
    }

    public class EdgeNode {
        public int index = 0;
        public int weight = 0;
        public EdgeNode next = null;

        public EdgeNode(int index, int weight) {
            this.index = index;
            this.weight = weight;
        }
    }

    public class VertexNode {
        public int value = 0;
        public EdgeNode next = null;

        public VertexNode(int value) {
            this.value = value;
        }
    }
}
