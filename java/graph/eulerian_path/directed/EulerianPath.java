package graph.eulerian_path.directed;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;

public class EulerianPath {
    public int[] search(VertexNode[] graphs) {
        int start = getStart(graphs);
        if (0 == ~start) {
            return new int[0];
        }

        boolean[][] visited = new boolean[graphs.length][graphs.length];
        for (int i = 0; i < graphs.length; ++i) {
            Arrays.fill(visited[i], false);
        }

        List<Integer> result = new ArrayList<>();
        search(graphs, start, visited, result);
        result.add(start);
        Collections.reverse(result);
        return result.stream().mapToInt(Integer::valueOf).toArray();
    }

    private void search(VertexNode[] graphs, int start, boolean[][] visited, List<Integer> result) {
        EdgeNode edge = graphs[start].next;
        while (null != edge) {
            int edgeIndex = edge.index;
            if (!visited[start][edgeIndex]) {
                visited[start][edgeIndex] = true;
                search(graphs, edgeIndex, visited, result);
                result.add(edgeIndex);
            }
            edge = edge.next;
        }
    }

    private int getStart(VertexNode[] graphs) {
        int[] inDegrees = new int[graphs.length];
        Arrays.fill(inDegrees, 0);
        int[] outDegrees = new int[graphs.length];
        Arrays.fill(outDegrees, 0);
        for (int i = 0; i < graphs.length; ++i) {
            EdgeNode edge = graphs[i].next;
            while (null != edge) {
                ++inDegrees[edge.index];
                ++outDegrees[i];
                edge = edge.next;
            }
        }

        int start = 0;
        int inCount = 0;
        int outCount = 0;
        for (int i = graphs.length - 1; i >= 0; --i) {
            if (Math.abs(inDegrees[i] - outDegrees[i]) > 1) {
                return -1;
            }

            if (1 == outDegrees[i] - inDegrees[i]) {
                start = i;
                ++inCount;
            } else if (1 == inDegrees[i] - outDegrees[i]) {
                ++outCount;
            }
            if (inCount > 1 || outCount > 1) {
                break;
            }
        }
        return ((0 == inCount && 0 == outCount) || (1 == inCount && 1 == outCount)) ? start : -1;
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
