package graph.maximum_flow;

import java.util.Arrays;
import java.util.Comparator;
import java.util.PriorityQueue;
import java.util.Queue;

public class HLPP {
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

        int[] gap = new int[graphs.length];
        Arrays.fill(gap, 0);
        int[] degrees = new int[graphs.length];
        Arrays.fill(degrees, 0);
        degrees[start] = graphs.length;
        Queue<HeapNode> queue = new PriorityQueue<>(cmp);
        int[] result = new int[graphs.length];
        Arrays.fill(result, 0);
        result[start] = Integer.MAX_VALUE;

        EdgeNode edge = graphs[start].next;
        while (null != edge) {
            int edgeIndex = edge.index;
            int value = Math.min(result[start], weights[start][edgeIndex]);
            weights[start][edgeIndex] -= value;
            weights[edgeIndex][start] += value;
            result[start] -= value;
            result[edgeIndex] += value;
            if (0 != value && edgeIndex != end) {
                queue.offer(new HeapNode(edgeIndex, degrees[edgeIndex]));
            }
            edge = edge.next;
        }

        while (!queue.isEmpty()) {
            HeapNode heap = queue.poll();
            int index = heap.index;
            if (0 != result[index]) {
                search(graphs, index, end, weights, gap, degrees, queue, result);
            }
        }
        return result[end];
    }

    private void search(VertexNode[] graphs, int start, int end, int[][] weights, int[] gap, int[] degrees, Queue<HeapNode> queue, int[] result) {
        EdgeNode edge = graphs[start].next;
        while (null != edge) {
            int edgeIndex = edge.index;
            if (degrees[start] == degrees[edgeIndex] + 1) {
                int value = Math.min(result[start], weights[start][edgeIndex]);
                weights[start][edgeIndex] -= value;
                weights[edgeIndex][start] += value;
                result[start] -= value;
                result[edgeIndex] += value;
                if (0 != value && edgeIndex != end) {
                    queue.offer(new HeapNode(edgeIndex, degrees[edgeIndex]));
                }
            }
            edge = edge.next;
        }

        if (start != end && 0 != result[start]) {
            --gap[degrees[start]];
            if (0 == ~gap[degrees[start]]) {
                for (int i = 0; i < graphs.length; ++i) {
                    if (i != end && degrees[i] > degrees[start] && degrees[i] < graphs.length) {
                        degrees[i]= graphs.length;
                    }
                }
            }
            ++degrees[start];
            if (degrees[start] < graphs.length) {
                ++gap[degrees[start]];
                queue.offer(new HeapNode(start, degrees[start]));
            }
        }
    }

    private class HeapNode {
        public int index = 0;
        public int degree = 0;

        public HeapNode(int index, int degree) {
            this.index = index;
            this.degree = degree;
        }
    }

    private static Comparator<HeapNode> cmp = new Comparator<HeapNode>() {
        @Override
        public int compare(HeapNode node1, HeapNode node2) {
            return node2.degree - node1.degree;
        }
    };

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
