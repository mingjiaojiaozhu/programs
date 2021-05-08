package graph.minimum_cost_maximum_flow;

import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;

public class Dinic {
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

        int[] minCost = new int[graphs.length];
        boolean[] visited = new boolean[graphs.length];
        Arrays.fill(visited, false);
        int[] result = new int[2];
        Arrays.fill(result, 0);
        while (searchOfBFS(graphs, start, end, weights, minCost)) {
            visited[end] = true;
            while (visited[end]) {
                Arrays.fill(visited, false);
                searchOfDFS(graphs, start, end, Integer.MAX_VALUE, weights, minCost, visited, result);
            }
        }
        return result;
    }

    private boolean searchOfBFS(VertexNode[] graphs, int start, int end, int[][] weights, int[] minCost) {
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

    private int searchOfDFS(VertexNode[] graphs, int start, int end, int flow, int[][] weights, int[] minCost, boolean[] visited, int[] result) {
        if (start == end) {
            visited[end] = true;
            result[0] += flow;
            return flow;
        }

        visited[start] = true;
        EdgeNode edge = graphs[start].next;
        int pivot = 0;
        while (null != edge) {
            int edgeIndex = edge.index;
            if ((!visited[edgeIndex] || edgeIndex == end) && 0 != weights[start][edgeIndex] && minCost[edgeIndex] == minCost[start] + edge.price) {
                int value = searchOfDFS(graphs, edgeIndex, end, Math.min(flow - pivot, weights[start][edgeIndex]), weights, minCost, visited, result);
                if (0 != value) {
                    pivot += value;
                    result[1] += value * edge.price;
                    weights[start][edgeIndex] -= value;
                    weights[edgeIndex][start] += value;
                    if (pivot == flow) {
                        break;
                    }
                }
            }
            edge = edge.next;
        }
        return pivot;
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
