package graph.minimum_cost_maximum_flow;

import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;

public class SPFA {
    public int[] search(VertexNode[] graphs, int start, int end) {
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
        int[] maxFlow = new int[graphs.length];
        int[] minCost = new int[graphs.length];
        int[] result = new int[2];
        Arrays.fill(result, 0);
        while (search(graphs, start, end, weights, parent, maxFlow, minCost)) {
            result[0] += maxFlow[end];
            result[1] += maxFlow[end] * minCost[end];

            int index = end;
            while (index != start) {
                weights[parent[index]][index] -= maxFlow[end];
                weights[index][parent[index]] += maxFlow[end];
                index = parent[index];
            }
        }
        return result;
    }

    private boolean search(VertexNode[] graphs, int start, int end, int[][] weights, int[] parent, int[] maxFlow, int[] minCost) {
        Arrays.fill(parent, -1);
        Arrays.fill(maxFlow, Integer.MAX_VALUE);
        Arrays.fill(minCost, Integer.MAX_VALUE);
        minCost[start] = 0;

        boolean[] visited = new boolean[graphs.length];
        Arrays.fill(visited, false);
        visited[start] = true;
        Queue<Integer> queue = new LinkedList<>();
        queue.offer(start);
        while (!queue.isEmpty()) {
            int index = queue.poll();
            visited[index] = false;
            EdgeNode edge = graphs[index].next;
            while (null != edge) {
                int edgeIndex = edge.index;
                if (0 != weights[index][edgeIndex] && minCost[edgeIndex] > minCost[index] + edge.price) {
                    parent[edgeIndex] = index;
                    maxFlow[edgeIndex] = Math.min(maxFlow[index], weights[index][edgeIndex]);
                    minCost[edgeIndex] = minCost[index] + edge.price;
                    if (!visited[edgeIndex]) {
                        visited[edgeIndex] = true;
                        queue.offer(edgeIndex);
                    }
                }
                edge = edge.next;
            }
        }
        return Integer.MAX_VALUE != minCost[end];
    }

    public class EdgeNode {
        public int index = 0;
        public int weight = 0;
        public int price = 0;
        public EdgeNode next = null;

        public EdgeNode(int index, int weight, int price) {
            this.index = index;
            this.weight = weight;
            this.price = price;
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
