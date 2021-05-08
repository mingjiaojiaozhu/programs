package graph.traversal;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;

public class BFS {
    public int[] traverse(VertexNode[] graphs, int start) {
        boolean[] visited = new boolean[graphs.length];
        Arrays.fill(visited, false);
        visited[start] = true;
        Queue<Integer> queue = new LinkedList<>();
        queue.offer(start);

        List<Integer> result = new ArrayList<>();
        result.add(start);
        while (!queue.isEmpty()) {
            int index = queue.poll();
            EdgeNode edge = graphs[index].next;
            while (null != edge) {
                int edgeIndex = edge.index;
                if (!visited[edgeIndex]) {
                    result.add(edgeIndex);
                    visited[edgeIndex] = true;
                    queue.offer(edgeIndex);
                }
                edge = edge.next;
            }
        }
        return result.stream().mapToInt(Integer::valueOf).toArray();
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
