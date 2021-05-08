package graph.topological_sort;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class TopologicalSort {
    public int[] sort(VertexNode[] graphs) {
        boolean[][] visited = new boolean[2][graphs.length];
        List<Integer> result = new ArrayList<>();
        for (int i = 0; i < graphs.length; ++i) {
            if (!visited[0][i] && !search(graphs, i, result, visited)) {
                return new int[0];
            }
        }
        Collections.reverse(result);
        return result.stream().mapToInt(Integer::valueOf).toArray();
    }

    private boolean search(VertexNode[] graphs, int start, List<Integer> result, boolean[][] visited) {
        visited[1][start] = true;
        EdgeNode edge = graphs[start].next;
        while (null != edge) {
            int edgeIndex = edge.index;
            if (visited[1][edgeIndex] || (!visited[0][edgeIndex] && !search(graphs, edgeIndex, result, visited))) {
                return false;
            }
            edge = edge.next;
        }

        visited[0][start] = true;
        visited[1][start] = false;
        result.add(start);
        return true;
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
