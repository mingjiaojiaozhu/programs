package graph.maximum_flow;

import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;

public class Dinic {
    public int search(VertexNode[] graphs, int start, int end) {
        int[][] weights = new int[graphs.length][graphs.length];
        for (int i = 0; i < graphs.length; ++i) {
            Arrays.fill(weights[i], 0);
            EdgeNode edge = graphs[i].next;
            while (null != edge) {
                weights[i][edge.index] = edge.weight;
                edge = edge.next;
            }
        }

        int[] parent = new int[graphs.length];
        int result = 0;
        while (searchOfBFS(graphs, start, end, weights, parent)) {
            result += searchOfDFS(graphs, start, end, Integer.MAX_VALUE, weights, parent);
        }
        return result;
    }

    private boolean searchOfBFS(VertexNode[] graphs, int start, int end, int[][] weights, int[] parent) {
        Arrays.fill(parent, -1);
        Queue<Integer> queue = new LinkedList<>();
        queue.offer(start);
        while (!queue.isEmpty()) {
            int index = queue.poll();
            EdgeNode edge = graphs[index].next;
            while (null != edge) {
                int edgeIndex = edge.index;
                if (0 != weights[index][edgeIndex] && 0 == ~parent[edgeIndex]) {
                    parent[edgeIndex] = index;
                    queue.offer(edgeIndex);
                }
                edge = edge.next;
            }
        }
        return 0 != ~parent[end];
    }

    private int searchOfDFS(VertexNode[] graphs, int start, int end, int flow, int[][] weights, int[] parent) {
        if (start == end) {
            return flow;
        }

        EdgeNode edge = graphs[start].next;
        while (null != edge) {
            int edgeIndex = edge.index;
            if (0 != weights[start][edgeIndex] && parent[edgeIndex] == start) {
                int value = searchOfDFS(graphs, edgeIndex, end, Math.min(flow, weights[start][edgeIndex]), weights, parent);
                if (0 != value) {
                    weights[start][edgeIndex] -= value;
                    weights[edgeIndex][start] += value;
                    return value;
                }
            }
            edge = edge.next;
        }
        return 0;
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
