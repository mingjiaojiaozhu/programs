package graph.shortest_path;

import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;

public class SPFA {
    public int[] search(VertexNode[] graphs, int start) {
        boolean[] visited = new boolean[graphs.length];
        Arrays.fill(visited, false);
        Queue<Integer> queue = new LinkedList<>();
        queue.offer(start);

        int[] result = new int[graphs.length];
        Arrays.fill(result, Integer.MAX_VALUE);
        result[start] = 0;

        int count = 0;
        while (!queue.isEmpty()) {
            int index = queue.poll();
            visited[index] = false;

            EdgeNode edge = graphs[index].next;
            while (null != edge) {
                int edgeIndex = edge.index;
                int edgeWeight = edge.weight;
                if (result[edgeIndex] > result[index] + edgeWeight) {
                    result[edgeIndex] = result[index] + edgeWeight;
                    if (!visited[edgeIndex]) {
                        queue.offer(edgeIndex);
                        visited[edgeIndex] = true;
                        ++count;
                    }
                }
                edge = edge.next;
            }
            if (count >= graphs.length) {
                return new int[0];
            }
        }
        return result;
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
