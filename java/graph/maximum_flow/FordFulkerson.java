package graph.maximum_flow;

import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;

public class FordFulkerson {
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
        Arrays.fill(parent, -1);
        int result = 0;
        while (search(graphs, start, end, weights, parent)) {
            int value = Integer.MAX_VALUE;
            int index = end;
            while (index != start) {
                if (value > weights[parent[index]][index]) {
                    value = weights[parent[index]][index];
                }
                index = parent[index];
            }

            index = end;
            while (index != start) {
                weights[parent[index]][index] -= value;
                weights[index][parent[index]] += value;
                index = parent[index];
            }
            result += value;
        }
        return result;
    }

    private boolean search(VertexNode[] graphs, int start, int end, int[][] weights, int[] parent) {
        boolean[] visited = new boolean[graphs.length];
        Arrays.fill(visited, false);
        visited[start] = true;
        Queue<Integer> queue = new LinkedList<>();
        queue.offer(start);
        while (!queue.isEmpty()) {
            int index = queue.poll();
            EdgeNode edge = graphs[index].next;
            while (null != edge) {
                int edgeIndex = edge.index;
                if (!visited[edgeIndex] && 0 != weights[index][edgeIndex]) {
                    parent[edgeIndex] = index;
                    visited[edgeIndex] = true;
                    queue.offer(edgeIndex);
                }
                edge = edge.next;
            }
        }
        return visited[end];
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
