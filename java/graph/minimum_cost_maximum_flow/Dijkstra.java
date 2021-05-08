package graph.minimum_cost_maximum_flow;

import java.util.Arrays;
import java.util.Comparator;
import java.util.PriorityQueue;
import java.util.Queue;

public class Dijkstra {
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
        int[] offset = new int[graphs.length];
        Arrays.fill(offset, 0);
        int[] result = new int[2];
        Arrays.fill(result, 0);
        while (search(graphs, start, end, weights, parent, maxFlow, minCost, offset)) {
            result[0] += maxFlow[end];
            result[1] += maxFlow[end] * (minCost[end] - offset[start] + offset[end]);

            int index = end;
            while (index != start) {
                weights[parent[index]][index] -= maxFlow[end];
                weights[index][parent[index]] += maxFlow[end];
                index = parent[index];
            }
            for (int i = 0; i < graphs.length; ++i) {
                offset[i] += minCost[i];
            }
        }
        return result;
    }

    private boolean search(VertexNode[] graphs, int start, int end, int[][] weights, int[] parent, int[] maxFlow, int[] minCost, int[] offset) {
        Arrays.fill(parent, -1);
        Arrays.fill(maxFlow, Integer.MAX_VALUE);
        Arrays.fill(minCost, Integer.MAX_VALUE);
        minCost[start] = 0;

        boolean[] visited = new boolean[graphs.length];
        Arrays.fill(visited, false);
        Queue<HeapNode> queue = new PriorityQueue<>(cmp);
        queue.offer(new HeapNode(start, minCost[start]));
        while (!queue.isEmpty()) {
            HeapNode heap = queue.poll();
            int index = heap.index;
            visited[index] = true;
            EdgeNode edge = graphs[index].next;
            while (null != edge) {
                int edgeIndex = edge.index;
                if (0 != weights[index][edgeIndex] && !visited[edgeIndex] && minCost[edgeIndex] > minCost[index] + edge.price + offset[index] - offset[edgeIndex]) {
                    parent[edgeIndex] = index;
                    maxFlow[edgeIndex] = Math.min(maxFlow[index], weights[index][edgeIndex]);
                    minCost[edgeIndex] = minCost[index] + edge.price + offset[index] - offset[edgeIndex];
                    queue.offer(new HeapNode(edgeIndex, minCost[edgeIndex]));
                }
                edge = edge.next;
            }
        }
        return Integer.MAX_VALUE != minCost[end];
    }

    private class HeapNode {
        public int index = 0;
        public int price = 0;

        public HeapNode(int index, int price) {
            this.index = index;
            this.price = price;
        }
    }

    private static Comparator<HeapNode> cmp = new Comparator<HeapNode>() {
        @Override
        public int compare(HeapNode node1, HeapNode node2) {
            return node1.price - node2.price;
        }
    };

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
